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

static void screen_list_1_item0_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        
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

void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen, screen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_list_1_item0, screen_list_1_item0_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_list_1_item1, screen_list_1_item1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_list_1_item2, screen_list_1_item2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_list_1_item3, screen_list_1_item3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_list_1_item4, screen_list_1_item4_event_handler, LV_EVENT_ALL, ui);
}

void events_init(lv_ui *ui)
{

}
