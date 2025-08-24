/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-23 13:37:56
 * @LastEditTime: 2025-08-24 14:40:54
 * @FilePath: \mini-smart-hub\Hardware\XPT2046.h
 * @Description:
 */
#ifndef __XPT2046_H
#define __XPT2046_H
#include "stm32f10x.h"
//==== XPT2046 软件SPI 引脚定义 ====//
#define XPT2046_CS_PORT GPIOF
#define XPT2046_CS_PIN GPIO_Pin_11

#define XPT2046_CLK_PORT GPIOB
#define XPT2046_CLK_PIN GPIO_Pin_1

#define XPT2046_MOSI_PORT GPIOF
#define XPT2046_MOSI_PIN GPIO_Pin_9

#define XPT2046_MISO_PORT GPIOB
#define XPT2046_MISO_PIN GPIO_Pin_2

#define XPT2046_PEN_PORT GPIOF
#define XPT2046_PEN_PIN GPIO_Pin_10

// CS控制
#define XPT2046_CS_LOW() GPIO_ResetBits(XPT2046_CS_PORT, XPT2046_CS_PIN)
#define XPT2046_CS_HIGH() GPIO_SetBits(XPT2046_CS_PORT, XPT2046_CS_PIN)

// CLK控制
#define XPT2046_CLK_LOW() GPIO_ResetBits(XPT2046_CLK_PORT, XPT2046_CLK_PIN)
#define XPT2046_CLK_HIGH() GPIO_SetBits(XPT2046_CLK_PORT, XPT2046_CLK_PIN)

// MOSI控制
#define XPT2046_MOSI_LOW() GPIO_ResetBits(XPT2046_MOSI_PORT, XPT2046_MOSI_PIN)
#define XPT2046_MOSI_HIGH() GPIO_SetBits(XPT2046_MOSI_PORT, XPT2046_MOSI_PIN)

// 读MISO
#define XPT2046_MISO_READ() GPIO_ReadInputDataBit(XPT2046_MISO_PORT, XPT2046_MISO_PIN)

// 读PENIRQ
#define XPT2046_PEN_READ() GPIO_ReadInputDataBit(XPT2046_PEN_PORT, XPT2046_PEN_PIN)

#define CMD_X 0xD0 // 读取X通道命令
#define CMD_Y 0x90 // 读取Y通道命令
void XPT2046_TouchInit(void);
uint8_t XPT2046_WriteByte(uint8_t data);
uint16_t XPT2046_ReadADC(uint8_t cmd);
void XPT2046_GetRawXY(uint16_t *x, uint16_t *y);
uint8_t XPT2046_GetAverageXY(uint16_t *x, uint16_t *y);
uint8_t XPT2046_Scan(uint16_t *x, uint16_t *y);
uint8_t XPT2046_IsPressed(void);
#endif
