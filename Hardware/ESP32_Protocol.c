/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-27 22:43:33
 * @LastEditTime: 2025-08-28 00:16:05
 * @FilePath: \mini-smart-hub\Hardware\ESP32_Protocol.c
 * @Description:
 */
#include "ESP32_Protocol.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include <stdint.h>
#include <stdbool.h>
ESP32Data_t esp32Data;
SemaphoreHandle_t esp32Mutex = NULL;

uint8_t esp32_buf[ESP32_PACKET_SIZE];
uint8_t esp32_index = 0;

void ESP32_Protocol_Init(void)
{
    if (esp32Mutex == NULL)
        esp32Mutex = xSemaphoreCreateMutex();
}

// 返回值：true = 完整帧解析完成
bool ProcessESP32Byte(uint8_t byte)
{
    // 丢弃非帧头字节
    if (esp32_index == 0 && byte != 0xFF)
        return false;

    // 保存字节
    esp32_buf[esp32_index++] = byte;

    // 判断是否到达完整帧
    if (esp32_index >= ESP32_PACKET_SIZE)
    {
        if (esp32_buf[6] == 0xFE)
        {
            // 完整包，更新全局数据
            if (esp32Mutex)
                xSemaphoreTake(esp32Mutex, portMAX_DELAY);

            esp32Data.light.brightness = esp32_buf[1];
            esp32Data.motor.mode = esp32_buf[2];
            esp32Data.motor.value = esp32_buf[3];
            esp32Data.servo.mode = esp32_buf[4];
            esp32Data.servo.value = esp32_buf[5];

            if (esp32Mutex)
                xSemaphoreGive(esp32Mutex);

            esp32_index = 0; // 准备下一包
            return true;     // 完整帧完成
        }
        else
        {
            // 尾字节错误，丢弃帧
            esp32_index = 0;
            return false;
        }
    }

    return false; // 未完成
}

ESP32Data_t GetESP32Data(void)
{
    ESP32Data_t temp;
    if (esp32Mutex)
        xSemaphoreTake(esp32Mutex, portMAX_DELAY);
    temp = esp32Data;
    if (esp32Mutex)
        xSemaphoreGive(esp32Mutex);
    return temp;
}