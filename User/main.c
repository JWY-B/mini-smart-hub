/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-19 20:56:31
 * @FilePath: \mini-smart-hub\User\main.c
 * @Description:
 */
#include "stm32f10x.h" // Device header
#include "LCD.h"
#include "Serial.h"
_lcd_dev lcddev = {
	.width = 480, // ST7796 默认分辨率
	.height = 320,
	.id = 0x0000,
	.dir = 0,		 // 0=竖屏，1=横屏
	.wramcmd = 0x2C, // 写GRAM命令
	.setxcmd = 0x2A, // 设置X坐标
	.setycmd = 0x2B	 // 设置Y坐标
};
int main(void)
{
	Serial_Init(); // 串口初始化
	LCD_Init();	   // LCD初始化
	// lcddev.id = LCD_ReadReg(0x0004);
	LCD_WR_REG(0XD3);
	lcddev.id = LCD_RD_DATA(); // dummy read
	lcddev.id = LCD_RD_DATA(); // 读到0X00
	lcddev.id = LCD_RD_DATA(); // 读取93
	lcddev.id <<= 8;
	lcddev.id |= LCD_RD_DATA(); // 读取41
	printf("%x", lcddev.id);
	while (1)
	{
	}
}