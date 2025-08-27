/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-26 21:47:45
 * @LastEditTime: 2025-08-27 19:24:24
 * @FilePath: \mini-smart-hub\User\Global.h
 * @Description:
 */

#ifndef __GLOBAL_H
#define __GLOBAL_H

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

typedef enum
{
    MOTOR_MODE_AUTO,  // 自动根据温度
    MOTOR_MODE_MANUAL // 手动设置速度
} MotorMode_t;

typedef struct
{
    MotorMode_t mode; // 模式
    uint16_t value;   // 手动时是速度(%)，自动时忽略
} MotorMessage_t;

typedef struct
{
    uint8_t brightness; // 0~100%
} LightMessage_t;

typedef struct
{
    uint8_t temperature;
    uint8_t humidity;
    LightMessage_t light;
    MotorMessage_t motor;
    MotorMessage_t servo;
} SystemStatus_t;

extern SystemStatus_t SystemStatus;
extern SemaphoreHandle_t System_mutex;

extern QueueHandle_t motorQueue;
extern QueueHandle_t servoQueue;
extern QueueHandle_t lightQueue;

extern QueueSetHandle_t queue_set;
#endif
