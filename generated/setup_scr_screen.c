/*
 * Copyright 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_screen(lv_ui *ui)
{
    // Write codes screen
    ui->screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen, 480, 320);
    lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_temp_arc
    ui->screen_temp_arc = lv_arc_create(ui->screen);
    lv_arc_set_mode(ui->screen_temp_arc, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->screen_temp_arc, 0, 50);
    lv_arc_set_bg_angles(ui->screen_temp_arc, 135, 45);
    lv_arc_set_value(ui->screen_temp_arc, 37);
    lv_arc_set_rotation(ui->screen_temp_arc, 0);
    lv_obj_set_style_arc_rounded(ui->screen_temp_arc, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui->screen_temp_arc, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->screen_temp_arc, 17, 26);
    lv_obj_set_size(ui->screen_temp_arc, 150, 150);

    // Write style for screen_temp_arc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_temp_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_temp_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->screen_temp_arc, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->screen_temp_arc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->screen_temp_arc, lv_color_hex(0xe6e6e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_temp_arc, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_temp_arc, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_temp_arc, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_temp_arc, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_temp_arc, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_temp_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for screen_temp_arc, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->screen_temp_arc, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->screen_temp_arc, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->screen_temp_arc, lv_color_hex(0xff93b2), LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Write style for screen_temp_arc, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_temp_arc, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_temp_arc, lv_color_hex(0xff0027), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_temp_arc, LV_GRAD_DIR_NONE, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->screen_temp_arc, 5, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes screen_humi_arc
    ui->screen_humi_arc = lv_arc_create(ui->screen);
    lv_arc_set_mode(ui->screen_humi_arc, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->screen_humi_arc, 0, 100);
    lv_arc_set_bg_angles(ui->screen_humi_arc, 135, 45);
    lv_arc_set_value(ui->screen_humi_arc, 70);
    lv_arc_set_rotation(ui->screen_humi_arc, 0);
    lv_obj_set_style_arc_rounded(ui->screen_humi_arc, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui->screen_humi_arc, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->screen_humi_arc, 175, 26);
    lv_obj_set_size(ui->screen_humi_arc, 150, 150);

    // Write style for screen_humi_arc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_humi_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_humi_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->screen_humi_arc, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->screen_humi_arc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->screen_humi_arc, lv_color_hex(0xe6e6e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_humi_arc, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_humi_arc, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_humi_arc, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_humi_arc, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_humi_arc, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_humi_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for screen_humi_arc, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->screen_humi_arc, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->screen_humi_arc, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->screen_humi_arc, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Write style for screen_humi_arc, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_humi_arc, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_humi_arc, lv_color_hex(0x0032ff), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_humi_arc, LV_GRAD_DIR_NONE, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->screen_humi_arc, 5, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes screen_temp_lable
    ui->screen_temp_lable = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_temp_lable, "temp");
    lv_label_set_long_mode(ui->screen_temp_lable, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_temp_lable, 43, 157);
    lv_obj_set_size(ui->screen_temp_lable, 100, 32);

    // Write style for screen_temp_lable, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_temp_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_temp_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_temp_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_temp_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_temp_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_temp_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_temp_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_temp_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_temp_lable, lv_color_hex(0xf56060), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_temp_lable, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_temp_lable, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_temp_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_temp_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_temp_lable, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_humi_label
    ui->screen_humi_label = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_humi_label, "humi");
    lv_label_set_long_mode(ui->screen_humi_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_humi_label, 203, 157);
    lv_obj_set_size(ui->screen_humi_label, 100, 32);

    // Write style for screen_humi_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_humi_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_humi_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_humi_label, lv_color_hex(0x2f52ff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_humi_label, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_humi_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_humi_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_humi_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_humi_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_humi_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_humi_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_humi_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_humi_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_humi_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_humi_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_Motor_list
    ui->screen_Motor_list = lv_dropdown_create(ui->screen);
    lv_dropdown_set_options(ui->screen_Motor_list, "AUTO\n25%\n50%\n75%\n100%");
    lv_obj_set_pos(ui->screen_Motor_list, 349, 36);
    lv_obj_set_size(ui->screen_Motor_list, 130, 30);

    // Write style for screen_Motor_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_Motor_list, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_Motor_list, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_Motor_list, lv_color_hex(0xe1e6ee), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_Motor_list, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_Motor_list, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_Motor_list, lv_color_hex(0x0D3055), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_Motor_list, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_Motor_list, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_Motor_list, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_Motor_list, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_Motor_list, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_Motor_list, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_Motor_list, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_Motor_list, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_Motor_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_CHECKED for &style_screen_Motor_list_extra_list_selected_checked
    static lv_style_t style_screen_Motor_list_extra_list_selected_checked;
    ui_init_style(&style_screen_Motor_list_extra_list_selected_checked);

    lv_style_set_border_width(&style_screen_Motor_list_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_screen_Motor_list_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_screen_Motor_list_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_Motor_list_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_Motor_list_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_screen_Motor_list_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_screen_Motor_list_extra_list_selected_checked, lv_color_hex(0xffa2d4));
    lv_style_set_bg_grad_dir(&style_screen_Motor_list_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_Motor_list), &style_screen_Motor_list_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    // Write style state: LV_STATE_DEFAULT for &style_screen_Motor_list_extra_list_main_default
    static lv_style_t style_screen_Motor_list_extra_list_main_default;
    ui_init_style(&style_screen_Motor_list_extra_list_main_default);

    lv_style_set_max_height(&style_screen_Motor_list_extra_list_main_default, 90);
    lv_style_set_text_color(&style_screen_Motor_list_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_Motor_list_extra_list_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_Motor_list_extra_list_main_default, 255);
    lv_style_set_border_width(&style_screen_Motor_list_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_screen_Motor_list_extra_list_main_default, 255);
    lv_style_set_border_color(&style_screen_Motor_list_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_Motor_list_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_Motor_list_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_screen_Motor_list_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_screen_Motor_list_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_Motor_list_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_Motor_list), &style_screen_Motor_list_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_screen_Motor_list_extra_list_scrollbar_default
    static lv_style_t style_screen_Motor_list_extra_list_scrollbar_default;
    ui_init_style(&style_screen_Motor_list_extra_list_scrollbar_default);

    lv_style_set_radius(&style_screen_Motor_list_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_Motor_list_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_Motor_list_extra_list_scrollbar_default, lv_color_hex(0xff00c0));
    lv_style_set_bg_grad_dir(&style_screen_Motor_list_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_Motor_list), &style_screen_Motor_list_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write codes screen_light_slider
    ui->screen_light_slider = lv_slider_create(ui->screen);
    lv_slider_set_range(ui->screen_light_slider, 20, 100);
    lv_slider_set_mode(ui->screen_light_slider, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->screen_light_slider, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_light_slider, 66, 205);
    lv_obj_set_size(ui->screen_light_slider, 160, 9);

    // Write style for screen_light_slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_light_slider, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_light_slider, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_light_slider, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_light_slider, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_light_slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_light_slider, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for screen_light_slider, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_light_slider, 8, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_light_slider, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_light_slider, lv_color_hex(0x19a65b), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_light_slider, LV_GRAD_DIR_NONE, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Write style for screen_light_slider, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_light_slider, 8, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_light_slider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_light_slider, lv_color_hex(0x2195f6), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_light_slider, LV_GRAD_DIR_NONE, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes screen_light_label
    ui->screen_light_label = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_light_label, "Screen_Light");
    lv_label_set_long_mode(ui->screen_light_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_light_label, 71, 227);
    lv_obj_set_size(ui->screen_light_label, 137, 17);

    // Write style for screen_light_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_light_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_light_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_light_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_light_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_light_label, lv_color_hex(0xf59000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_light_label, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_light_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_light_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_light_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_light_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_light_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_light_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_light_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_light_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_Servo_list
    ui->screen_Servo_list = lv_dropdown_create(ui->screen);
    lv_dropdown_set_options(ui->screen_Servo_list, "AUTO\n25%\n50%\n75%\n100%");
    lv_obj_set_pos(ui->screen_Servo_list, 349, 199);
    lv_obj_set_size(ui->screen_Servo_list, 130, 30);

    // Write style for screen_Servo_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_Servo_list, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_Servo_list, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_Servo_list, lv_color_hex(0xe1e6ee), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_Servo_list, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_Servo_list, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_Servo_list, lv_color_hex(0x0D3055), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_Servo_list, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_Servo_list, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_Servo_list, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_Servo_list, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_Servo_list, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_Servo_list, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_Servo_list, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_Servo_list, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_Servo_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_CHECKED for &style_screen_Servo_list_extra_list_selected_checked
    static lv_style_t style_screen_Servo_list_extra_list_selected_checked;
    ui_init_style(&style_screen_Servo_list_extra_list_selected_checked);

    lv_style_set_border_width(&style_screen_Servo_list_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_screen_Servo_list_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_screen_Servo_list_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_Servo_list_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_Servo_list_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_screen_Servo_list_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_screen_Servo_list_extra_list_selected_checked, lv_color_hex(0x92a8ff));
    lv_style_set_bg_grad_dir(&style_screen_Servo_list_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_Servo_list), &style_screen_Servo_list_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    // Write style state: LV_STATE_DEFAULT for &style_screen_Servo_list_extra_list_main_default
    static lv_style_t style_screen_Servo_list_extra_list_main_default;
    ui_init_style(&style_screen_Servo_list_extra_list_main_default);

    lv_style_set_max_height(&style_screen_Servo_list_extra_list_main_default, 90);
    lv_style_set_text_color(&style_screen_Servo_list_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_Servo_list_extra_list_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_Servo_list_extra_list_main_default, 255);
    lv_style_set_border_width(&style_screen_Servo_list_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_screen_Servo_list_extra_list_main_default, 255);
    lv_style_set_border_color(&style_screen_Servo_list_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_screen_Servo_list_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_screen_Servo_list_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_screen_Servo_list_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_screen_Servo_list_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_Servo_list_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_Servo_list), &style_screen_Servo_list_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_screen_Servo_list_extra_list_scrollbar_default
    static lv_style_t style_screen_Servo_list_extra_list_scrollbar_default;
    ui_init_style(&style_screen_Servo_list_extra_list_scrollbar_default);

    lv_style_set_radius(&style_screen_Servo_list_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_Servo_list_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_Servo_list_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_screen_Servo_list_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->screen_Servo_list), &style_screen_Servo_list_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write codes screen_temp_value
    ui->screen_temp_value = lv_spangroup_create(ui->screen);
    lv_spangroup_set_align(ui->screen_temp_value, LV_TEXT_ALIGN_LEFT);
    lv_spangroup_set_overflow(ui->screen_temp_value, LV_SPAN_OVERFLOW_CLIP);
    lv_spangroup_set_mode(ui->screen_temp_value, LV_SPAN_MODE_BREAK);
    // create span
    ui->screen_temp_value_span = lv_spangroup_new_span(ui->screen_temp_value);
    lv_span_set_text(ui->screen_temp_value_span, "20");
    lv_style_set_text_color(&ui->screen_temp_value_span->style, lv_color_hex(0xf00000));
    lv_style_set_text_decor(&ui->screen_temp_value_span->style, LV_TEXT_DECOR_NONE);
    lv_style_set_text_font(&ui->screen_temp_value_span->style, &lv_font_montserratMedium_16);
    lv_obj_set_pos(ui->screen_temp_value, 70, 96);
    lv_obj_set_size(ui->screen_temp_value, 60, 38);

    // Write style state: LV_STATE_DEFAULT for &style_screen_temp_value_main_main_default
    static lv_style_t style_screen_temp_value_main_main_default;
    ui_init_style(&style_screen_temp_value_main_main_default);

    lv_style_set_border_width(&style_screen_temp_value_main_main_default, 0);
    lv_style_set_radius(&style_screen_temp_value_main_main_default, 0);
    lv_style_set_bg_opa(&style_screen_temp_value_main_main_default, 0);
    lv_style_set_pad_top(&style_screen_temp_value_main_main_default, 0);
    lv_style_set_pad_right(&style_screen_temp_value_main_main_default, 0);
    lv_style_set_pad_bottom(&style_screen_temp_value_main_main_default, 0);
    lv_style_set_pad_left(&style_screen_temp_value_main_main_default, 0);
    lv_style_set_shadow_width(&style_screen_temp_value_main_main_default, 0);
    lv_obj_add_style(ui->screen_temp_value, &style_screen_temp_value_main_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_spangroup_refr_mode(ui->screen_temp_value);

    // Write codes screen_humi_value
    ui->screen_humi_value = lv_spangroup_create(ui->screen);
    lv_spangroup_set_align(ui->screen_humi_value, LV_TEXT_ALIGN_LEFT);
    lv_spangroup_set_overflow(ui->screen_humi_value, LV_SPAN_OVERFLOW_CLIP);
    lv_spangroup_set_mode(ui->screen_humi_value, LV_SPAN_MODE_BREAK);
    // create span
    ui->screen_humi_value_span = lv_spangroup_new_span(ui->screen_humi_value);
    lv_span_set_text(ui->screen_humi_value_span, "40");
    lv_style_set_text_color(&ui->screen_humi_value_span->style, lv_color_hex(0x3000ff));
    lv_style_set_text_decor(&ui->screen_humi_value_span->style, LV_TEXT_DECOR_NONE);
    lv_style_set_text_font(&ui->screen_humi_value_span->style, &lv_font_montserratMedium_16);
    lv_obj_set_pos(ui->screen_humi_value, 230, 96);
    lv_obj_set_size(ui->screen_humi_value, 60, 31);

    // Write style state: LV_STATE_DEFAULT for &style_screen_humi_value_main_main_default
    static lv_style_t style_screen_humi_value_main_main_default;
    ui_init_style(&style_screen_humi_value_main_main_default);

    lv_style_set_border_width(&style_screen_humi_value_main_main_default, 0);
    lv_style_set_radius(&style_screen_humi_value_main_main_default, 0);
    lv_style_set_bg_opa(&style_screen_humi_value_main_main_default, 0);
    lv_style_set_pad_top(&style_screen_humi_value_main_main_default, 0);
    lv_style_set_pad_right(&style_screen_humi_value_main_main_default, 0);
    lv_style_set_pad_bottom(&style_screen_humi_value_main_main_default, 0);
    lv_style_set_pad_left(&style_screen_humi_value_main_main_default, 0);
    lv_style_set_shadow_width(&style_screen_humi_value_main_main_default, 0);
    lv_obj_add_style(ui->screen_humi_value, &style_screen_humi_value_main_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_spangroup_refr_mode(ui->screen_humi_value);

    // Write codes screen_servo_lable
    ui->screen_servo_lable = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_servo_lable, "Servo");
    lv_label_set_long_mode(ui->screen_servo_lable, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_servo_lable, 357, 239);
    lv_obj_set_size(ui->screen_servo_lable, 100, 32);

    // Write style for screen_servo_lable, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_servo_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_servo_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_servo_lable, lv_color_hex(0x675fff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_servo_lable, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_servo_lable, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_servo_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_servo_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_servo_lable, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_servo_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_servo_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_servo_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_servo_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_servo_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_servo_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_motor_label
    ui->screen_motor_label = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_motor_label, "Motor");
    lv_label_set_long_mode(ui->screen_motor_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_motor_label, 363, 7);
    lv_obj_set_size(ui->screen_motor_label, 100, 32);

    // Write style for screen_motor_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_motor_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_motor_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_motor_label, lv_color_hex(0xf77d7d), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_motor_label, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_motor_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_motor_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_motor_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_motor_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_motor_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_motor_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_motor_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_motor_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_motor_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_motor_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // The custom code of screen.

    // Update current screen layout.
    lv_obj_update_layout(ui->screen);

    // Init events for screen.
    events_init_screen(ui);
}
