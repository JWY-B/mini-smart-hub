/*
 * Copyright 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "Global.h"
#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif
static const uint16_t motorSpeeds[] = {25, 50, 75, 100};
static void screen_Motor_list_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
    {
        uint16_t id = lv_dropdown_get_selected(guider_ui.screen_Motor_list);
        MotorMessage_t motor_message;
        if (id == 0)
        { // Auto 模式
            motor_message.mode = MOTOR_MODE_AUTO;
            motor_message.value = 0;
        }
        else
        { // 手动模式
            motor_message.mode = MOTOR_MODE_MANUAL;
            motor_message.value = motorSpeeds[id - 1];
        }
        xQueueSend(motorQueue, &motor_message, 0);
        break;
    }
    default:
        break;
    }
}

static void screen_light_slider_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    LightMessage_t light_message;
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
    {
        // LCD_Backlight_SetBrightness(lv_slider_get_value(guider_ui.screen_light_slider));
        light_message.brightness = lv_slider_get_value(guider_ui.screen_light_slider);
        xQueueSend(lightQueue, &light_message, 0);
        break;
    }
    default:
        break;
    }
}

static void screen_Servo_list_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
    {
        uint16_t id = lv_dropdown_get_selected(guider_ui.screen_Servo_list);
        MotorMessage_t Servo_message;
        if (id == 0)
        {
            Servo_message.mode = MOTOR_MODE_AUTO;
            Servo_message.value = 0;
        }
        else
        {
            Servo_message.mode = MOTOR_MODE_MANUAL;
            Servo_message.value = motorSpeeds[id - 1];
        }
        xQueueSend(servoQueue, &Servo_message, 0);
        break;
    }
    default:
        break;
    }
}

void events_init_screen(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_Motor_list, screen_Motor_list_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_light_slider, screen_light_slider_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_Servo_list, screen_Servo_list_event_handler, LV_EVENT_ALL, ui);
}

void events_init(lv_ui *ui)
{
}
