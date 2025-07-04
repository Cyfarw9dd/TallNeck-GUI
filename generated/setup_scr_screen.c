/*
* Copyright 2024 NXP
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

// 声明list_container_event_handler函数
extern void list_container_event_handler(lv_event_t *e);

void setup_scr_screen(lv_ui *ui)
{
    //Write codes screen
    ui->screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen, 240, 536);
    lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_cont_1
    ui->screen_cont_1 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_1, 0, 0);
    lv_obj_set_size(ui->screen_cont_1, 240, 536);
    lv_obj_set_scrollbar_mode(ui->screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    // 创建一个新的容器来包裹列表
    lv_obj_t *list_container = lv_obj_create(ui->screen_cont_1);
    lv_obj_set_pos(list_container, 0, 79);
    lv_obj_set_size(list_container, 240, 360);
    lv_obj_set_scrollbar_mode(list_container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(list_container, LV_DIR_VER);
    lv_obj_clear_flag(list_container, LV_OBJ_FLAG_SCROLLABLE);  // 禁用容器的滚动
    lv_obj_set_style_border_width(list_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(list_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(list_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_event_cb(list_container, list_container_event_handler, LV_EVENT_ALL, NULL);

    //Write codes screen_list_1
    ui->screen_list_1 = lv_list_create(list_container);
    lv_obj_set_scroll_dir(ui->screen_list_1, LV_DIR_VER);  // 只允许垂直滚动
    lv_obj_clear_flag(ui->screen_list_1, LV_OBJ_FLAG_SCROLL_MOMENTUM);  // 禁用惯性滚动
    lv_obj_clear_flag(ui->screen_list_1, LV_OBJ_FLAG_SCROLL_CHAIN);  // 禁用滚动链
    lv_obj_clear_flag(ui->screen_list_1, LV_OBJ_FLAG_SCROLL_ELASTIC);  // 禁用弹性滚动
    ui->screen_list_1_item0 = lv_list_add_btn(ui->screen_list_1, &_orbit_alpha_60x60, "Orbit Tracking");
    ui->screen_list_1_item1 = lv_list_add_btn(ui->screen_list_1, &_time_alpha_60x60, "Sync Time");
    ui->screen_list_1_item2 = lv_list_add_btn(ui->screen_list_1, &_file_search_alpha_60x60, "File Search");
    ui->screen_list_1_item3 = lv_list_add_btn(ui->screen_list_1, &_download_alpha_60x60, "Download TLE");
    ui->screen_list_1_item4 = lv_list_add_btn(ui->screen_list_1, &_eph_grey_alpha_60x60, "Sync Location");
    lv_obj_set_pos(ui->screen_list_1, 0, 0);
    lv_obj_set_size(ui->screen_list_1, 240, 360);
    lv_obj_set_scrollbar_mode(ui->screen_list_1, LV_SCROLLBAR_MODE_ACTIVE);

    // 为每个列表项禁用水平滚动
    lv_obj_set_scroll_dir(ui->screen_list_1_item0, LV_DIR_VER);
    lv_obj_set_scroll_dir(ui->screen_list_1_item1, LV_DIR_VER);
    lv_obj_set_scroll_dir(ui->screen_list_1_item2, LV_DIR_VER);
    lv_obj_set_scroll_dir(ui->screen_list_1_item3, LV_DIR_VER);
    lv_obj_set_scroll_dir(ui->screen_list_1_item4, LV_DIR_VER);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_1_main_main_default
    static lv_style_t style_screen_list_1_main_main_default;
    ui_init_style(&style_screen_list_1_main_main_default);

    lv_style_set_pad_top(&style_screen_list_1_main_main_default, 5);
    lv_style_set_pad_left(&style_screen_list_1_main_main_default, 5);
    lv_style_set_pad_right(&style_screen_list_1_main_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_list_1_main_main_default, 5);
    lv_style_set_bg_opa(&style_screen_list_1_main_main_default, 255);
    lv_style_set_bg_color(&style_screen_list_1_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_1_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_list_1_main_main_default, 1);
    lv_style_set_border_opa(&style_screen_list_1_main_main_default, 255);
    lv_style_set_border_color(&style_screen_list_1_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_border_side(&style_screen_list_1_main_main_default, LV_BORDER_SIDE_FULL | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT);
    lv_style_set_radius(&style_screen_list_1_main_main_default, 3);
    lv_style_set_shadow_width(&style_screen_list_1_main_main_default, 0);
    lv_obj_add_style(ui->screen_list_1, &style_screen_list_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_1_main_scrollbar_default
    static lv_style_t style_screen_list_1_main_scrollbar_default;
    ui_init_style(&style_screen_list_1_main_scrollbar_default);

    lv_style_set_radius(&style_screen_list_1_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_screen_list_1_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_screen_list_1_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_1_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->screen_list_1, &style_screen_list_1_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_1_extra_btns_main_default
    static lv_style_t style_screen_list_1_extra_btns_main_default;
    ui_init_style(&style_screen_list_1_extra_btns_main_default);

    lv_style_set_pad_top(&style_screen_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_screen_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_screen_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_list_1_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_screen_list_1_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_screen_list_1_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_list_1_extra_btns_main_default, &lv_customer_font_montserratMedium_20);
    lv_style_set_text_opa(&style_screen_list_1_extra_btns_main_default, 255);
    lv_style_set_radius(&style_screen_list_1_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_screen_list_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_list_1_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_1_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->screen_list_1_item3, &style_screen_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_list_1_item2, &style_screen_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_list_1_item1, &style_screen_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_list_1_item0, &style_screen_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_list_1_item4, &style_screen_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_list_1_extra_texts_main_default
    static lv_style_t style_screen_list_1_extra_texts_main_default;
    ui_init_style(&style_screen_list_1_extra_texts_main_default);

    lv_style_set_pad_top(&style_screen_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_screen_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_screen_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_list_1_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_screen_list_1_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_screen_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_screen_list_1_extra_texts_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_list_1_extra_texts_main_default, 255);
    lv_style_set_radius(&style_screen_list_1_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_screen_list_1_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_screen_list_1_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_screen_list_1_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_screen_list_1_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //Write codes screen_cont_2
    ui->screen_cont_2 = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_2, 0, 0);
    lv_obj_set_size(ui->screen_cont_2, 240, 81);
    lv_obj_set_scrollbar_mode(ui->screen_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_cont_2, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_cont_2, LV_BORDER_SIDE_FULL | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_img_1
    ui->screen_img_1 = lv_img_create(ui->screen);
    lv_obj_add_flag(ui->screen_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_1, &_sat_alpha_64x64);
    lv_img_set_pivot(ui->screen_img_1, 50,50);
    lv_img_set_angle(ui->screen_img_1, 0);
    lv_obj_set_pos(ui->screen_img_1, 16, 9);
    lv_obj_set_size(ui->screen_img_1, 64, 64);

    //Write style for screen_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_label_1
    ui->screen_label_1 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_1, "TallNeck");
    lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_1, 89, 22);
    lv_obj_set_size(ui->screen_label_1, 130, 46);

    //Write style for screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_1, &lv_font_NotoSans_VariableFont_wdth_wght_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen);

    //Init events for screen.
    events_init_screen(ui);
}
