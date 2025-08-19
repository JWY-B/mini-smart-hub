/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-17 19:09:07
 * @LastEditTime: 2025-08-19 19:39:43
 * @FilePath: \mini-smart-hub\Hardware\LCD.h
 * @Description:
 */
#ifndef __LCD_H
#define __LCD_H

// LCD寄存器结构体
typedef struct
{
    volatile uint16_t LCD_REG; // 控制寄存器
    volatile uint16_t LCD_RAM; // 数据寄存器
} LCD_TypeDef;

#define LCD_BASE ((uint32_t)(0x6C000000 | 0x000007FE))
#define LCD ((LCD_TypeDef *)LCD_BASE)

// LCD
typedef struct
{
    uint16_t width;   // 屏幕宽度
    uint16_t height;  // 屏幕高度
    uint16_t id;      // 屏幕ID
    uint8_t dir;      // 屏幕方向
    uint16_t wramcmd; // 写GRAM命令
    uint16_t setxcmd; // 设置X坐标命令
    uint16_t setycmd; // 设置Y坐标命令
} _lcd_dev;
extern _lcd_dev lcddev; // LCD设备结构体

uint16_t LCD_ReadReg(uint16_t LCD_Reg);
void LCD_Init(void);
uint16_t LCD_RD_DATA(void);
#endif
