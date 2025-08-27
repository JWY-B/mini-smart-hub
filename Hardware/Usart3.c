/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-27 20:50:48
 * @LastEditTime: 2025-08-27 22:07:22
 * @FilePath: \mini-smart-hub\Hardware\Usart3.c
 * @Description:
 */
#include "Usart3.h"
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

QueueHandle_t usart3_rxQueue = NULL;
SemaphoreHandle_t usart3_mutex = NULL;

void USART3_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // USART3_TX -> PB10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // USART3_RX -> PB11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 配置USART3
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART3, &USART_InitStructure);

    // 开启中断
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; // FreeRTOS 建议优先级 >=5
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART3, ENABLE);

    // 创建接收队列 & 发送互斥锁
    usart3_rxQueue = xQueueCreate(64, sizeof(uint8_t));
    usart3_mutex = xSemaphoreCreateMutex();
}

void USART3_IRQHandler(void)
{
    if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
    {
        uint8_t RxData = USART_ReceiveData(USART3);

        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xQueueSendFromISR(usart3_rxQueue, &RxData, &xHigherPriorityTaskWoken);

        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void USART3_SendByte(uint8_t byte)
{
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
        ;
    USART_SendData(USART3, byte);
}

void USART3_SendString(const char *str)
{
    if (usart3_mutex)
        xSemaphoreTake(usart3_mutex, portMAX_DELAY);

    while (*str)
    {
        USART3_SendByte(*str++);
    }

    if (usart3_mutex)
        xSemaphoreGive(usart3_mutex);
}

void USART3_SendArray(uint8_t *array, uint16_t length)
{
    if (usart3_mutex)
        xSemaphoreTake(usart3_mutex, portMAX_DELAY);

    for (uint16_t i = 0; i < length; i++)
    {
        USART3_SendByte(array[i]);
    }

    if (usart3_mutex)
        xSemaphoreGive(usart3_mutex);
}
