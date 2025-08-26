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
#include "PWM.h"
#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

static void screen_Motor_list_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
    {
        uint16_t id = lv_dropdown_get_selected(guider_ui.screen_Motor_list);

        switch (id)
        {
        case (0):
        {

            break;
        }
        case (1):
        {
            Motor_SetSpeed(25);
            break;
        }
        case (2):
        {
            Motor_SetSpeed(50);
            break;
        }
        case (3):
        {
            Motor_SetSpeed(75);
            break;
        }
        case (4):
        {
            Motor_SetSpeed(100);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen_light_slider_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
    {
        LCD_Backlight_SetBrightness(lv_slider_get_value(guider_ui.screen_light_slider));
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

        switch (id)
        {
        case (0):
        {

            break;
        }
        case (1):
        {
            Motor_SetSpeed2(25);
            break;
        }
        case (2):
        {
            Motor_SetSpeed2(50);
            break;
        }
        case (3):
        {
            Motor_SetSpeed2(75);
            break;
        }
        case (4):
        {
            Motor_SetSpeed2(100);
            break;
        }
        default:
            break;
        }
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
