/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-26 19:58:13
 * @LastEditTime: 2025-08-27 15:44:57
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

    MotorMessage_t motor_message;
    motor_message.mode = MOTOR_MODE_AUTO;
    motor_message.value = 0; // 自动模式初始值
    xQueueSend(motorQueue, &motor_message, 0);

    // 同时设置下拉列表显示为 Auto
    lv_dropdown_set_selected(guider_ui.screen_Motor_list, 0);

    while (1)
    {
        if (xSemaphoreTake(dht11_mutex, pdMS_TO_TICKS(20)) == pdTRUE)
        {
            float t = dht11_data.temperature;
            float h = dht11_data.humidity;
            xSemaphoreGive(dht11_mutex);

            // 在LVGL界面显示温湿度
            sprintf(buf, "%.1f C", t);
            lv_arc_set_value(guider_ui.screen_temp_arc, (int16_t)t);
            lv_span_set_text(guider_ui.screen_temp_value_span, buf);
            sprintf(buf, "%.1f%%", h);
            lv_arc_set_value(guider_ui.screen_humi_arc, (int16_t)h);
            lv_span_set_text(guider_ui.screen_humi_value_span, buf);
        }
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(50));
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
            if (xSemaphoreTake(dht11_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
            {
                dht11_data.temperature = (float)temp;
                dht11_data.humidity = (float)humi;
                xSemaphoreGive(dht11_mutex);
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
        if (xSemaphoreTake(dht11_mutex, pdMS_TO_TICKS(10)) == pdTRUE)
        {
            temp = dht11_data.temperature;
            humi = dht11_data.humidity;
            xSemaphoreGive(dht11_mutex);
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
            }
        }
        else if (activated_queue == lightQueue)
        {
            if (xQueueReceive(lightQueue, &light_msg, 0) == pdPASS)
            {
                LCD_Backlight_SetBrightness(light_msg.brightness);
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
        }
    }
}