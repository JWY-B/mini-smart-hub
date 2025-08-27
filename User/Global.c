/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-27 12:14:15
 * @LastEditTime: 2025-08-27 15:37:22
 * @FilePath: \mini-smart-hub\User\Global.c
 * @Description:
 */
#include "Global.h"
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "queue.h"

// 队列句柄定义
QueueHandle_t motorQueue = NULL;
QueueHandle_t servoQueue = NULL;
QueueHandle_t lightQueue = NULL;
QueueSetHandle_t queue_set;
// 队列初始化函数
void Queue_Init(void)
{

    motorQueue = xQueueCreate(5, sizeof(MotorMessage_t));
    servoQueue = xQueueCreate(5, sizeof(MotorMessage_t));
    lightQueue = xQueueCreate(5, sizeof(LightMessage_t));

    queue_set = xQueueCreateSet(5 + 5 + 5);

    xQueueAddToSet(motorQueue, queue_set);
    xQueueAddToSet(servoQueue, queue_set);
    xQueueAddToSet(lightQueue, queue_set);
}
