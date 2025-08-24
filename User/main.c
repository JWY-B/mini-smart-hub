/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-24 14:26:21
 * @FilePath: \mini-smart-hub\User\main.c
 * @Description:
 */
#include "stm32f10x.h" // Device header
#include "LCD.h"
#include "Serial.h"
#include "XPT2046.h"
extern _lcd_dev lcddev = {
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

	LCD_Fill(0, 0, 320, 480, 0x0000); // White
									  //	LCD_DrawLine(100, 200, 200, 300, 0xFFFF);
	// LCD_DrawPoint(10, 10, 0xF800);
	// LCD_ShowString(0, 300, "0 320", 16, 1, 0xffff, 0xCCCC);
	// LCD_ShowString(400, 0, "480 0", 16, 1, 0xffff, 0xCCCC);
	// LCD_ShowString(0, 0, "0 0", 16, 1, 0xffff, 0xCCCC);
	// LCD_ShowString(400, 300, "480 320", 16, 1, 0xffff, 0xCCCC);
	XPT2046_TouchInit();
	uint16_t x, y;
	uint16_t sumx[2], sumy[2];
	while (1)
	{
		if (XPT2046_Scan(&x, &y))
		{
			sumx[1] = x;
			sumy[1] = y;
			// �ɹ���ȡ������
			printf("Touch: X=%d, Y=%d\r\n", x, y);
			if (abs(sumx[1] - sumx[0]) < 10 && abs(sumy[1] - sumy[0]) < 10)
			{
				/* code */
				LCD_DrawPoint(x, y, 0xffff);
			}

			sumx[0] = sumx[1];
			sumy[0] = sumy[1];
		}
	}
}