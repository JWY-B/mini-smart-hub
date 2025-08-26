/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-26 13:14:02
 * @FilePath: \智能家居中控系统\mini-smart-hub\User\main.c
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
// #include "setup_scr_screen.c"

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
	XPT2046_TouchInit();
	lv_init();			  // LVGL 初始化
	lv_port_disp_init();  // 注册LVGL的显示任务
	lv_port_indev_init(); // 注册LVGL的触屏检测任务
	TIM3_Init();
	DHT11_Init();
	setup_ui(&guider_ui);
	events_init(&guider_ui);
	uint8_t temp, humi;
	char buf[8];
	lv_obj_clear_flag(guider_ui.screen_temp_arc, LV_OBJ_FLAG_CLICKABLE);
	while (1)
	{
		DHT11_Read_Data(&humi, &temp);
		sprintf(buf, "%d", temp);

		printf("temp %d ,humi %d\r\n", humi, temp);
		// delay_ms(1000);
		lv_arc_set_value(guider_ui.screen_temp_arc, temp);
		lv_span_set_text(guider_ui.screen_temp_value_span, buf);
		lv_timer_handler();
		//  1. 测试 LCD 背光从 0% ~ 100%
	}
}