/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#include "globals.h"
#include "get_tle.h"
#include "sgp4sdp4.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "gui_guider.h"

// 添加一个事件处理函数来阻止列表区域的水平滑动
void list_container_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_GESTURE) {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if (dir == LV_DIR_LEFT || dir == LV_DIR_RIGHT) {
            // 阻止水平方向的滑动
            lv_indev_wait_release(lv_indev_get_act());
        }
    }
}

static void screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            // 移除向左滑动切换到screen_1的代码
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

// 合并orbit_tracking按钮的事件处理函数
static void screen_list_1_item0_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        // 点击时切换到orbit_tracking屏幕
        setup_scr_orbit_tracking(&guider_ui);
        lv_scr_load(guider_ui.orbit_tracking_screen);
        break;
    }
    default:
        break;
    }
}

static void screen_list_1_item1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        sntp_netif_sync_time();
        break;
    }
    default:
        break;
    }
}

static void screen_list_1_item2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        get_file_info();
        break;
    }
    default:
        break;
    }
}

static void screen_list_1_item3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        xTaskNotify(tle_download_handler, UPDATE_TLE, eSetValueWithOverwrite);
        break;
    }
    default:
        break;
    }
}

static void screen_list_1_item4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        // TODO: Add GPS location update functionality here
        break;
    }
    default:
        break;
    }
}

// 添加orbit_tracking屏幕的事件处理函数
static void orbit_tracking_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            // 向右滑动返回主屏幕
            lv_scr_load(guider_ui.screen);
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

// 卫星列表项点击事件处理
static void satellite_item_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    
    if (code == LV_EVENT_CLICKED) {
        // 获取被点击的列表项索引
        for (int i = 0; i < 10; i++) {
            if (target == guider_ui.satellite_items[i]) {
                // TODO: 处理卫星选择事件
                // 这里可以添加选择卫星后的处理逻辑
                break;
            }
        }
    }
}

void events_init_screen (lv_ui *ui)
{
    // 使用更安全的方式注册事件处理函数
    if (ui->screen != NULL) {
        lv_obj_add_event_cb(ui->screen, screen_event_handler, LV_EVENT_ALL, ui);
    }
    
    if (ui->screen_list_1_item0 != NULL) {
        lv_obj_add_event_cb(ui->screen_list_1_item0, screen_list_1_item0_event_handler, LV_EVENT_ALL, ui);
    }
    
    if (ui->screen_list_1_item1 != NULL) {
        lv_obj_add_event_cb(ui->screen_list_1_item1, screen_list_1_item1_event_handler, LV_EVENT_ALL, ui);
    }
    
    if (ui->screen_list_1_item2 != NULL) {
        lv_obj_add_event_cb(ui->screen_list_1_item2, screen_list_1_item2_event_handler, LV_EVENT_ALL, ui);
    }
    
    if (ui->screen_list_1_item3 != NULL) {
        lv_obj_add_event_cb(ui->screen_list_1_item3, screen_list_1_item3_event_handler, LV_EVENT_ALL, ui);
    }
    
    if (ui->screen_list_1_item4 != NULL) {
        lv_obj_add_event_cb(ui->screen_list_1_item4, screen_list_1_item4_event_handler, LV_EVENT_ALL, ui);
    }
}

void events_init_orbit_tracking(lv_ui *ui)
{
    // 使用更安全的方式注册事件处理函数
    if (ui->orbit_tracking_screen != NULL) {
        lv_obj_add_event_cb(ui->orbit_tracking_screen, orbit_tracking_screen_event_handler, LV_EVENT_ALL, ui);
    }

    // 为每个卫星列表项添加事件处理
    for (int i = 0; i < 10; i++) {
        if (ui->satellite_items[i] != NULL) {
            lv_obj_add_event_cb(ui->satellite_items[i], satellite_item_event_handler, LV_EVENT_CLICKED, NULL);
        }
    }
}

void events_init(lv_ui *ui)
{
    // 先初始化主屏幕事件
    events_init_screen(ui);
    
    // 只有在orbit_tracking屏幕已经创建的情况下才初始化其事件
    if (ui->orbit_tracking_screen != NULL) {
        events_init_orbit_tracking(ui);
    }
}
