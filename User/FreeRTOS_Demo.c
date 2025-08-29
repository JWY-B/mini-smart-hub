/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-26 19:58:13
 * @LastEditTime: 2025-08-28 01:25:52
 * @FilePath: \mini-smart-hub\User\FreeRTOS_Demo.c
 * @Description:
 */
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOS.h"
#include "lvgl.h"          // 它为整个LVGL提供了更完整的头文件引用
#include "lv_port_disp.h"  // LVGL的显示支持
#include "lv_port_indev.h" // LVGL的触屏支持
#include "stm32f10x.h"     // Device header
#include "LCD.h"
#include "Serial.h"
#include "XPT2046.h"
#include "Delay.h"
#include <stdlib.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "DHT11.h"
#include "Global.h"
#include "queue.h"
#include "PWM.h"
#include "GuiUtil.h"
#include "Usart3.h"
#include "ESP32_Protocol.h"
lv_ui guider_ui;
SystemStatus_t SystemStatus;
SemaphoreHandle_t System_mutex;

/* 启动任务的配置 */
#define START_TASK_STACK 128
#define START_TASK_PRIORITY 1
TaskHandle_t start_task_handle;
void start_task(void *pvParameters);

/* GUI任务的配置 */
#define GUI_TASK_STACK 1024
#define GUI_TASK_PRIORITY 4
TaskHandle_t GUI_handle;
void GUI_task(void *pvParameters);

/* DHT11任务的配置 */
#define DHT11_TASK_STACK 128
#define DHT11_TASK_PRIORITY 2
TaskHandle_t DHT11_handle;
void DHT11_task(void *pvParameters);

/* Control任务的配置 */
#define Control_TASK_STACK 128
#define Control_TASK_PRIORITY 3
TaskHandle_t Control_handle;
void Control_task(void *pvParameters);

/* SendToESP32任务的配置 */
#define SendToESP32_TASK_STACK 128
#define SendToESP32_TASK_PRIORITY 1
TaskHandle_t SendToESP32_handle;
void SendToESP32_task(void *pvParameters);

/* ReceiveToESP32任务的配置 */
#define ReceiveToESP32_TASK_STACK 128
#define ReceiveToESP32_TASK_PRIORITY 3
TaskHandle_t ReceiveToESP32_handle;
void ReceiveToESP32_task(void *pvParameters);

void freertos_start(void)
{
    /* 1.创建一个启动任务 */
    xTaskCreate((TaskFunction_t)start_task,               // 任务函数的地址
                (char *)"start_task",                     // 任务名字符串
                (configSTACK_DEPTH_TYPE)START_TASK_STACK, // 任务栈大小，默认最小128，单位4字节
                (void *)NULL,                             // 传递给任务的参数
                (UBaseType_t)START_TASK_PRIORITY,         // 任务的优先级
                (TaskHandle_t *)&start_task_handle);      // 任务句柄的地址

    /* 2.启动调度器:会自动创建空闲任务 */
    vTaskStartScheduler();
}

void start_task(void *pvParameters)
{
    /* 进入临界区:保护临界区里的代码不会被打断 */
    taskENTER_CRITICAL();

    USART3_Init(115200);
    Serial_Init();
    System_mutex = xSemaphoreCreateMutex();
    if (System_mutex == NULL)
    {
        printf("create mutex failed\r\n");
    }
    TaskHandle_t GUI_handle;

    xTaskCreate((TaskFunction_t)GUI_task,
                (char *)"GUI",
                (configSTACK_DEPTH_TYPE)GUI_TASK_STACK,
                (void *)NULL,
                (UBaseType_t)GUI_TASK_PRIORITY,
                (TaskHandle_t *)&GUI_handle);

    TaskHandle_t DHT11_handle;

    xTaskCreate((TaskFunction_t)DHT11_task,
                (char *)"DHT11",
                (configSTACK_DEPTH_TYPE)DHT11_TASK_STACK,
                (void *)NULL,
                (UBaseType_t)DHT11_TASK_PRIORITY,
                (TaskHandle_t *)&DHT11_handle);

    xTaskCreate((TaskFunction_t)Control_task,
                (char *)"Control",
                (configSTACK_DEPTH_TYPE)Control_TASK_STACK,
                (void *)NULL,
                (UBaseType_t)Control_TASK_PRIORITY,
                (TaskHandle_t *)&Control_handle);

    xTaskCreate((TaskFunction_t)SendToESP32_task,
                (char *)"SendToESP32",
                (configSTACK_DEPTH_TYPE)SendToESP32_TASK_STACK,
                (void *)NULL,
                (UBaseType_t)SendToESP32_TASK_PRIORITY,
                (TaskHandle_t *)&SendToESP32_handle);

    xTaskCreate((TaskFunction_t)ReceiveToESP32_task,
                (char *)"ReceiveToESP32",
                (configSTACK_DEPTH_TYPE)ReceiveToESP32_TASK_STACK,
                (void *)NULL,
                (UBaseType_t)ReceiveToESP32_TASK_PRIORITY,
                (TaskHandle_t *)&ReceiveToESP32_handle);

    vTaskDelete(NULL);

    /* 退出临界区 */
    taskEXIT_CRITICAL();
}

void GUI_task(void *pvParameters)
{
    Queue_Init(); // Serial_Init(); // 串口初始化
    LCD_Init();   // LCD初始化
    XPT2046_TouchInit();
    lv_init();            // LVGL 初始化
    lv_port_disp_init();  // 注册LVGL的显示任务
    lv_port_indev_init(); // 注册LVGL的触屏检测任务
    setup_ui(&guider_ui);
    events_init(&guider_ui);

    char buf[32];
    SystemStatus_t LocalStatus;

    while (1)
    {
        if (xSemaphoreTake(System_mutex, pdMS_TO_TICKS(20)) == pdTRUE)
        {
            LocalStatus = SystemStatus;
            xSemaphoreGive(System_mutex);
            float t = LocalStatus.temperature;
            float h = LocalStatus.humidity;
            // 在LVGL界面显示温湿度
            sprintf(buf, "%.1f C", t);
            lv_arc_set_value(guider_ui.screen_temp_arc, (int16_t)t);
            lv_span_set_text(guider_ui.screen_temp_value_span, buf);
            sprintf(buf, "%.1f%%", h);
            lv_arc_set_value(guider_ui.screen_humi_arc, (int16_t)h);
            lv_span_set_text(guider_ui.screen_humi_value_span, buf);
            lv_dropdown_set_selected(guider_ui.screen_Motor_list,
                                     LocalStatus.motor.mode == MOTOR_MODE_AUTO ? 0 : get_motor_dropdown_index(LocalStatus.motor));

            lv_dropdown_set_selected(guider_ui.screen_Servo_list,
                                     LocalStatus.servo.mode == MOTOR_MODE_AUTO ? 0 : get_motor_dropdown_index(LocalStatus.servo));
            lv_slider_set_value(guider_ui.screen_light_slider, LocalStatus.light.brightness, LV_ANIM_OFF);
        }
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(25));
    }
}

void DHT11_task(void *pvParameters)
{
    uint8_t temp, humi;

    DHT11_Init();

    while (1)
    {
        if (DHT11_Read_Data(&humi, &temp) == 0)
        {
            if (xSemaphoreTake(System_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
            {
                SystemStatus.temperature = temp;
                SystemStatus.humidity = humi;
                xSemaphoreGive(System_mutex);
            }
        }
        else
        {
            printf("DHT11 read error\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Control_task(void *pvParameters)
{
    MotorMessage_t motor_msg;
    MotorMessage_t servo_msg;
    LightMessage_t light_msg;
    uint8_t temp = 0, humi = 0;
    while (1)
    {
        if (xSemaphoreTake(System_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
        {
            temp = SystemStatus.temperature;
            humi = SystemStatus.humidity;
            xSemaphoreGive(System_mutex);
        }
        QueueSetMemberHandle_t activated_queue;
        activated_queue = xQueueSelectFromSet(queue_set, portMAX_DELAY);

        if (activated_queue == motorQueue)
        {
            if (xQueueReceive(motorQueue, &motor_msg, 0) == pdPASS)
            {
                // 电机控制逻辑
                if (motor_msg.mode == MOTOR_MODE_AUTO)
                {
                    // 根据温度设置速度
                    if (temp < 25)
                        motor_msg.value = 25;
                    else if (temp < 27)
                        motor_msg.value = 50;
                    else if (temp < 30)
                        motor_msg.value = 75;
                    else
                        motor_msg.value = 100;
                }
                Motor_SetSpeed(motor_msg.value);
                if (xSemaphoreTake(System_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
                {
                    SystemStatus.motor = motor_msg; // 更新全局状态
                    xSemaphoreGive(System_mutex);
                }
            }
        }
        else if (activated_queue == lightQueue)
        {
            if (xQueueReceive(lightQueue, &light_msg, 0) == pdPASS)
            {
                LCD_Backlight_SetBrightness(light_msg.brightness);
                if (xSemaphoreTake(System_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
                {
                    SystemStatus.light = light_msg; // 更新全局状态
                    xSemaphoreGive(System_mutex);
                }
            }
        }
        else if (activated_queue == servoQueue)
        {
            if (xQueueReceive(servoQueue, &servo_msg, 0) == pdPASS)
            {
                if (servo_msg.mode == MOTOR_MODE_AUTO)
                {
                    if (humi < 40)
                        servo_msg.value = 25;
                    else if (humi < 60)
                        servo_msg.value = 50;
                    else if (humi < 80)
                        servo_msg.value = 75;
                    else
                        servo_msg.value = 100;
                }
            }
            Motor_SetSpeed2(servo_msg.value);
            if (xSemaphoreTake(System_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
            {
                SystemStatus.servo = servo_msg; // 更新全局状态
                xSemaphoreGive(System_mutex);
            }
        }
        SystemStatus_t local_status;
        if (xSemaphoreTake(System_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
        {
            local_status = SystemStatus;
            xSemaphoreGive(System_mutex);
        }
    }
}
void SendToESP32_task(void *pvParameters)
{
    SystemStatus_t LocalStatus;
    uint8_t data[9];
    data[0] = 0xFF;
    data[8] = 0xFE;

    while (1)
    {
        // 发送数据到ESP32
        if (xSemaphoreTake(System_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
        {
            LocalStatus = SystemStatus;
            xSemaphoreGive(System_mutex);
            data[1] = LocalStatus.temperature;
            data[2] = LocalStatus.humidity;
            data[3] = LocalStatus.light.brightness;
            data[4] = LocalStatus.motor.mode;
            data[5] = LocalStatus.motor.value;
            data[6] = LocalStatus.servo.mode;
            data[7] = LocalStatus.servo.value;
            USART3_SendArray(data, 9);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void ReceiveToESP32_task(void *pvParameters)
{
    ESP32_Protocol_Init();
    uint8_t rxByte;
    ESP32Data_t data;
    char buf[128];
    int len;
    MotorMessage_t motor_msg;
    MotorMessage_t servo_msg;
    LightMessage_t light_msg;
    while (1)
    {
        if (xQueueReceive(usart3_rxQueue, &rxByte, portMAX_DELAY) == pdPASS)
        {
            // 只有完整帧解析完成才打印
            if (ProcessESP32Byte(rxByte))
            {
                data = GetESP32Data(); // 线程安全获取
                data.light.brightness = (data.light.brightness < 20) ? 20 : (data.light.brightness > 100) ? 100
                                                                                                          : data.light.brightness;

                data.motor.mode = (data.motor.mode == 0) ? 0 : 1;
                data.motor.value = (data.motor.value <= 25) ? 25 : (data.motor.value <= 50) ? 50
                                                               : (data.motor.value < 75)    ? 75
                                                                                            : 100;

                data.servo.mode = (data.servo.mode == 0) ? 0 : 1;
                data.servo.value = (data.servo.value <= 25) ? 25 : (data.servo.value <= 50) ? 50
                                                               : (data.servo.value <= 75)   ? 75
                                                                                            : 100;

                light_msg.brightness = data.light.brightness;
                motor_msg.mode = data.motor.mode;
                motor_msg.value = data.motor.value;
                servo_msg.mode = data.servo.mode;
                servo_msg.value = data.servo.value;
                xQueueSend(lightQueue, &light_msg, 0);
                xQueueSend(motorQueue, &motor_msg, 0);
                xQueueSend(servoQueue, &servo_msg, 0);

                if (xSemaphoreTake(System_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
                {
                    SystemStatus.light.brightness = data.light.brightness;
                    SystemStatus.motor.mode = data.motor.mode;
                    SystemStatus.motor.value = data.motor.value;
                    SystemStatus.servo.mode = data.servo.mode;
                    SystemStatus.servo.value = data.servo.value;
                    xSemaphoreGive(System_mutex);
                }
            }
        }
    }
}