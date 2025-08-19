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
	.width = 480, // ST7796 Ĭ�Ϸֱ���
	.height = 320,
	.id = 0x0000,
	.dir = 0,		 // 0=������1=����
	.wramcmd = 0x2C, // дGRAM����
	.setxcmd = 0x2A, // ����X����
	.setycmd = 0x2B	 // ����Y����
};
int main(void)
{
	Serial_Init(); // ���ڳ�ʼ��
	LCD_Init();	   // LCD��ʼ��
	// lcddev.id = LCD_ReadReg(0x0004);
	LCD_WR_REG(0XD3);
	lcddev.id = LCD_RD_DATA(); // dummy read
	lcddev.id = LCD_RD_DATA(); // ����0X00
	lcddev.id = LCD_RD_DATA(); // ��ȡ93
	lcddev.id <<= 8;
	lcddev.id |= LCD_RD_DATA(); // ��ȡ41
	printf("%x", lcddev.id);
	while (1)
	{
	}
}