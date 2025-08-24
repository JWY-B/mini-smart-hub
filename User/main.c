/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-24 21:17:56
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
extern _lcd_dev lcddev = {
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
	// LCD_Fill(0, 0, 320, 480, 0x0000); // White
	XPT2046_TouchInit();
	lv_init();			  // LVGL 初始化
	lv_port_disp_init();  // 注册LVGL的显示任务
	lv_port_indev_init(); // 注册LVGL的触屏检测任务
	TIM3_Init();
	// 按钮
	lv_obj_t *myBtn = lv_btn_create(lv_scr_act()); // 创建按钮; 父对象：当前活动屏幕
	lv_obj_set_pos(myBtn, 1, 1);				   // 设置坐标
	lv_obj_set_size(myBtn, 120, 50);			   // 设置大小

	// 按钮上的文本
	lv_obj_t *label_btn = lv_label_create(myBtn);	// 创建文本标签，父对象：上面的btn按钮
	lv_obj_align(label_btn, LV_ALIGN_CENTER, 0, 0); // 对齐于：父对象
	lv_label_set_text(label_btn, "Test");			// 设置标签的文本

	// 独立的标签
	lv_obj_t *myLabel = lv_label_create(lv_scr_act());			   // 创建文本标签; 父对象：当前活动屏幕
	lv_label_set_text(myLabel, "Hello world!");					   // 设置标签的文本
	lv_obj_align(myLabel, LV_ALIGN_CENTER, 0, 0);				   // 对齐于：父对象
	lv_obj_align_to(myBtn, myLabel, LV_ALIGN_OUT_TOP_MID, 0, -20); // 对齐于：某对象

// 左上角 红
lv_obj_t *tl = lv_obj_create(lv_scr_act());
lv_obj_set_size(tl, 30, 30);
lv_obj_set_style_bg_color(tl, lv_color_hex(0xFF0000), 0);
lv_obj_set_pos(tl, 0, 0);

// 右下角 绿（假设 480x320）
lv_obj_t *br = lv_obj_create(lv_scr_act());
lv_obj_set_size(br, 30, 30);
lv_obj_set_style_bg_color(br, lv_color_hex(0x00FF00), 0);
lv_obj_set_pos(br, LV_HOR_RES - 30, LV_VER_RES - 30);
	while (1)
	{
			lv_timer_handler();
	}
}