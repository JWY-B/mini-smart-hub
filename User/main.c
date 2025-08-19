/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-20 00:07:32
 * @FilePath: \mini-smart-hub\User\main.c
 * @Description:
 */
#include "stm32f10x.h" // Device header
#include "LCD.h"
#include "Serial.h"
_lcd_dev lcddev = {
	.width = 320,	 // ���
	.height = 480,	 // �߶�
	.id = 0x0000,	 // ST7796 ID
	.dir = 0,		 // 0=����
	.wramcmd = 0x2C, // дGRAM����
	.setxcmd = 0x2A, // ����X��������
	.setycmd = 0x2B	 // ����Y��������
};
// ���ô���
void LCD_SetWindow(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
    // �е�ַ (X)
    LCD_WR_REG(0x2A);
    LCD_WR_DATA(xs >> 8);
    LCD_WR_DATA(xs & 0xFF);
    LCD_WR_DATA(xe >> 8);
    LCD_WR_DATA(xe & 0xFF);

    // �е�ַ (Y)
    LCD_WR_REG(0x2B);
    LCD_WR_DATA(ys >> 8);
    LCD_WR_DATA(ys & 0xFF);
    LCD_WR_DATA(ye >> 8);
    LCD_WR_DATA(ye & 0xFF);

    LCD_WR_REG(0x2C); // ��ʼдGRAM
}
// ����/���������ɫ
void LCD_Fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
    uint32_t total = (xe - xs + 1) * (ye - ys + 1);
    uint32_t i;

    LCD_SetWindow(xs, ys, xe, ye);

    for (i = 0; i < total; i++)
    {
        LCD->LCD_RAM = color; // ֱ����GRAMд���ݣ�FSMCӳ�䣩
    }
}
int main(void)
{
	Serial_Init(); // ���ڳ�ʼ��
	LCD_Init();	   // LCD��ʼ��
	// lcddev.id = LCD_ReadReg(0x0004);
	LCD_WR_REG(0xD3);
	lcddev.id = LCD_RD_DATA(); // dummy read
	lcddev.id = LCD_RD_DATA(); // ����0X00
	lcddev.id = LCD_RD_DATA(); // ��ȡ93
	lcddev.id <<= 8;
	lcddev.id |= LCD_RD_DATA(); // ��ȡ41
	printf("%x\r\n", lcddev.id);
	LCD_Fill(0, 0, 320, 480, 0xFFFF); // White
	while (1)
	{
	}
}