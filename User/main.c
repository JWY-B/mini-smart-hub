/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-20 22:50:13
 * @FilePath: \mini-smart-hub\User\main.c
 * @Description:
 */
#include "stm32f10x.h" // Device header
#include "LCD.h"
#include "Serial.h"
_lcd_dev lcddev = {
	.width = 480,	 // 宽度
	.height = 320,	 // 高度
	.id = 0x0000,	 // ST7796 ID
	.dir = 1,		 // 0=竖屏 1=横屏
	.wramcmd = 0x2C, // 写GRAM命令
	.setxcmd = 0x2A, // 设置X坐标命令
	.setycmd = 0x2B	 // 设置Y坐标命令
};

// 设置窗口
void LCD_SetWindow(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
	// 列地址 (X)
	LCD_WR_REG(0x2A);
	LCD_WR_DATA(xs >> 8);
	LCD_WR_DATA(xs & 0xFF);
	LCD_WR_DATA(xe >> 8);
	LCD_WR_DATA(xe & 0xFF);

	// 行地址 (Y)
	LCD_WR_REG(0x2B);
	LCD_WR_DATA(ys >> 8);
	LCD_WR_DATA(ys & 0xFF);
	LCD_WR_DATA(ye >> 8);
	LCD_WR_DATA(ye & 0xFF);

	LCD_WR_REG(0x2C); // 开始写GRAM
}
// 整屏/区域填充颜色
void LCD_Fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
	uint32_t total = (xe - xs + 1) * (ye - ys + 1);
	uint32_t i;

	LCD_SetWindow(xs, ys, xe, ye);

	for (i = 0; i < total; i++)
	{
		LCD->LCD_RAM = color; // 直接往GRAM写数据（FSMC映射）
	}
}

int main(void)
{
	Serial_Init(); // 串口初始化
	LCD_Init();	   // LCD初始化

	LCD_Fill(0, 0, 320, 480, 0xFFFF); // White
	LCD_ShowChar(100, 100, 'B', 16, 1);
	while (1)
	{
	}
}