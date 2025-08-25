/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-25 17:53:00
 * @FilePath: \mini-smart-hub\User\main.c
 * @Description:
 */

#include "lvgl.h"		   // ��Ϊ����LVGL�ṩ�˸�������ͷ�ļ�����
#include "lv_port_disp.h"  // LVGL����ʾ֧��
#include "lv_port_indev.h" // LVGL�Ĵ���֧��
#include "stm32f10x.h"	   // Device header
#include "LCD.h"
#include "Serial.h"
#include "XPT2046.h"
#include "Delay.h"
#include <stdlib.h>
#include "TIM3.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "DHT11.h"
extern _lcd_dev lcddev = {
	.width = 480,	 // ���
	.height = 320,	 // �߶�
	.id = 0x0000,	 // ST7796 ID
	.dir = 1,		 // 0=���� 1=����
	.wramcmd = 0x2C, // дGRAM����
	.setxcmd = 0x2A, // ����X��������
	.setycmd = 0x2B	 // ����Y��������
};
lv_ui guider_ui;
int main(void)
{
	Serial_Init(); // ���ڳ�ʼ��
	LCD_Init();	   // LCD��ʼ��
	// LCD_Fill(0, 0, 320, 480, 0x0000); // White
	XPT2046_TouchInit();
	lv_init();			  // LVGL ��ʼ��
	lv_port_disp_init();  // ע��LVGL����ʾ����
	lv_port_indev_init(); // ע��LVGL�Ĵ����������
	TIM3_Init();
	DHT11_Init();
	setup_ui(&guider_ui);
	events_init(&guider_ui);
	uint8_t temp,humi;
	while (1)
	{
		DHT11_Read_Data(&temp,&humi);
		printf("temp %d ,humi %d\r\n",humi,temp);
		delay_ms(1000);
		//lv_timer_handler();
	}
}