/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-24 21:17:56
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
	// LCD_Fill(0, 0, 320, 480, 0x0000); // White
	XPT2046_TouchInit();
	lv_init();			  // LVGL ��ʼ��
	lv_port_disp_init();  // ע��LVGL����ʾ����
	lv_port_indev_init(); // ע��LVGL�Ĵ����������
	TIM3_Init();
	// ��ť
	lv_obj_t *myBtn = lv_btn_create(lv_scr_act()); // ������ť; �����󣺵�ǰ���Ļ
	lv_obj_set_pos(myBtn, 1, 1);				   // ��������
	lv_obj_set_size(myBtn, 120, 50);			   // ���ô�С

	// ��ť�ϵ��ı�
	lv_obj_t *label_btn = lv_label_create(myBtn);	// �����ı���ǩ�������������btn��ť
	lv_obj_align(label_btn, LV_ALIGN_CENTER, 0, 0); // �����ڣ�������
	lv_label_set_text(label_btn, "Test");			// ���ñ�ǩ���ı�

	// �����ı�ǩ
	lv_obj_t *myLabel = lv_label_create(lv_scr_act());			   // �����ı���ǩ; �����󣺵�ǰ���Ļ
	lv_label_set_text(myLabel, "Hello world!");					   // ���ñ�ǩ���ı�
	lv_obj_align(myLabel, LV_ALIGN_CENTER, 0, 0);				   // �����ڣ�������
	lv_obj_align_to(myBtn, myLabel, LV_ALIGN_OUT_TOP_MID, 0, -20); // �����ڣ�ĳ����

// ���Ͻ� ��
lv_obj_t *tl = lv_obj_create(lv_scr_act());
lv_obj_set_size(tl, 30, 30);
lv_obj_set_style_bg_color(tl, lv_color_hex(0xFF0000), 0);
lv_obj_set_pos(tl, 0, 0);

// ���½� �̣����� 480x320��
lv_obj_t *br = lv_obj_create(lv_scr_act());
lv_obj_set_size(br, 30, 30);
lv_obj_set_style_bg_color(br, lv_color_hex(0x00FF00), 0);
lv_obj_set_pos(br, LV_HOR_RES - 30, LV_VER_RES - 30);
	while (1)
	{
			lv_timer_handler();
	}
}