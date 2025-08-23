/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-17 19:09:07
 * @LastEditTime: 2025-08-24 00:12:07
 * @FilePath: \mini-smart-hub\Hardware\LCD.h
 * @Description: st7796驱动
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

void LCD_WR_REG(uint16_t regval);
void LCD_WR_DATA(uint16_t data);
uint16_t LCD_RD_DATA(void);
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t LCD_ReadReg(uint16_t LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
void LCD_Init(void);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
uint16_t LCD_ReadPoint(uint16_t x, uint16_t y);
void LCD_ShowChar(uint16_t Xpos, uint16_t Ypos, uint8_t num, uint8_t size, uint8_t mode, uint16_t point_color, uint16_t back_color);
void LCD_ShowString(uint16_t x, uint16_t y,
                    const char *p, uint8_t size, uint8_t mode,
                    uint16_t point_color, uint16_t back_color);
void LCD_SetWindow(uint16_t x0, uint16_t y0,
                   uint16_t x1, uint16_t y1);
void LCD_Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_Clear(uint16_t color);
void LCD_DrawLine(uint16_t x0, uint16_t y0,
                  uint16_t x1, uint16_t y1,
                  uint16_t color);

#endif
