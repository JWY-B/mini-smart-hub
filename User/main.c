/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-23 13:00:26
 * @FilePath: \mini-smart-hub\User\main.c
 * @Description:
 */
#include "stm32f10x.h" // Device header
#include "LCD.h"
#include "Serial.h"
_lcd_dev lcddev = {
	.width = 480,	 // ���
	.height = 320,	 // �߶�
	.id = 0x0000,	 // ST7796 ID
	.dir = 1,		 // 0=���� 1=����
	.wramcmd = 0x2C, // дGRAM����
	.setxcmd = 0x2A, // ����X��������
	.setycmd = 0x2B	 // ����Y��������
};
int main(void)
{
	Serial_Init(); // ���ڳ�ʼ��
	LCD_Init();	   // LCD��ʼ��

	LCD_Fill(0, 0, 320, 480, 0xCCCC); // White
	LCD_ShowChar(100, 100, 'A', 16, 1, 0xffff, 0xCCCC);
	LCD_DrawLine(100, 200, 200, 300, 0xFFFF);

	LCD_ShowString(100, 200, "Hello World!", 16, 1, 0xffff, 0xCCCC);
	while (1)
	{
	}
}