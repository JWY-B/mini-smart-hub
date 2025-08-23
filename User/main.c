/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-24 00:12:47
 * @FilePath: \mini-smart-hub\User\main.c
 * @Description:
 */
#include "stm32f10x.h" // Device header
#include "LCD.h"
#include "Serial.h"
#include "XPT2046.h"
_lcd_dev lcddev = {
	.width = 480,	 // 宽度
	.height = 320,	 // 高度
	.id = 0x0000,	 // ST7796 ID
	.dir = 1,		 // 0=竖屏 1=横屏
	.wramcmd = 0x2C, // 写GRAM命令
	.setxcmd = 0x2A, // 设置X坐标命令
	.setycmd = 0x2B	 // 设置Y坐标命令
};

int main(void)
{
	Serial_Init(); // 串口初始化
	LCD_Init();	   // LCD初始化

	LCD_Fill(0, 0, 320, 480, 0xCCCC); // White
	LCD_ShowChar(0, 303, 'A', 16, 1, 0xffff, 0xCCCC);
	LCD_DrawLine(100, 200, 200, 300, 0xFFFF);
	LCD_DrawPoint(10, 10, 0xF800);
	LCD_ShowString(0, 0, "Hello World!", 16, 1, 0xffff, 0xCCCC);

	XPT2046_TouchInit();
	uint16_t x, y;
	while (1)
	{
		if (XPT2046_Scan(&x, &y))
		{
			// 成功读取触摸点
			printf("Touch: X=%d, Y=%d\r\n", x, y);
		}
	}
}