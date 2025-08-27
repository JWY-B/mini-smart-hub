/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-27 23:48:18
 * @FilePath: \mini-smart-hub\User\main.c
 * @Description:
 */
#include "FreeRTOS.h"
#include "task.h"
#include "lvgl.h"		   // ��Ϊ����LVGL�ṩ�˸�������ͷ�ļ�����
#include "lv_port_disp.h"  // LVGL����ʾ֧��
#include "lv_port_indev.h" // LVGL�Ĵ���֧��
#include "stm32f10x.h"	   // Device header
#include "LCD.h"
#include "Serial.h"
#include "XPT2046.h"
#include "Delay.h"
#include <stdlib.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "DHT11.h"
#include "FreeRTOS_Demo.h"
#include "semphr.h"
#include "Global.h"
#include "Usart3.h"
void vApplicationTickHook(void)
{
	lv_tick_inc(1);
}

int main(void)
{
	// USART3_Init();
	freertos_start();
	while (1)
	{
	}
}