/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-25 17:53:00
 * @FilePath: \mini-smart-hub\User\main.c
 * @Description:
 */

#include "lvgl.h"		   // 它为整个LVGL提供了更完整的头文件引用
#include "lv_port_disp.h"  // LVGL的显示支持
#include "lv_port_indev.h" // LVGL的触屏支持
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
	.width = 480,	 // 宽度
	.height = 320,	 // 高度
	.id = 0x0000,	 // ST7796 ID
	.dir = 1,		 // 0=竖屏 1=横屏
	.wramcmd = 0x2C, // 写GRAM命令
	.setxcmd = 0x2A, // 设置X坐标命令
	.setycmd = 0x2B	 // 设置Y坐标命令
};
lv_ui guider_ui;
int main(void)
{
	Serial_Init(); // 串口初始化
	LCD_Init();	   // LCD初始化
	// LCD_Fill(0, 0, 320, 480, 0x0000); // White
	XPT2046_TouchInit();
	lv_init();			  // LVGL 初始化
	lv_port_disp_init();  // 注册LVGL的显示任务
	lv_port_indev_init(); // 注册LVGL的触屏检测任务
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