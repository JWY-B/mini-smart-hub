#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"
#include "DHT11.h"
#include "Delay.h"

#define OUT 1
#define IN 0
#define DHT11_DATA_PIN GPIO_Pin_1
#define DHT11_PORT GPIOA
#define DHT11_HIGH GPIO_SetBits(DHT11_PORT, DHT11_DATA_PIN)
#define DHT11_LOW GPIO_ResetBits(DHT11_PORT, DHT11_DATA_PIN)
#define DHT11_READ_PIN GPIO_ReadInputDataBit(DHT11_PORT, DHT11_DATA_PIN)

void DHT11_Init(void);
void DHT11_Mode(uint8_t mode);
uint8_t DHT11_Start(void);
uint8_t DHT11_Read_Bit(void);
uint8_t DHT11_Read_Byte(void);
uint8_t DHT11_Read_Data(uint8_t *humidity, uint8_t *temperature);
#endif
