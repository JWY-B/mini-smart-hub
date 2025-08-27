#ifndef USART3_H_
#define USART3_H_
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "stm32f10x.h"
extern QueueHandle_t usart3_rxQueue;

void USART3_Init(uint32_t baudrate);
void USART3_IRQHandler(void);
void USART3_SendByte(uint8_t byte);
void USART3_SendString(const char *str);
void USART3_SendArray(uint8_t *array, uint16_t length);

#endif