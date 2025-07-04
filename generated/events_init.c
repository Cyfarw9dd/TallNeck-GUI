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
#include "lvgl_display.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "gui_guider.h"
#include "custom.h"
#include "esp_log.h"

static const char *TAG = "sync_location";

// 声明外部函数
void setup_scr_sat_param(lv_ui *ui);

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

static void screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
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

static void screen_list_1_item0_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        setup_scr_orbit_tracking(&guider_ui);
        lv_scr_load(guider_ui.orbit_tracking_screen);
        break;
    }
    default:
        break;
    }
}

static void screen_list_1_item1_event_handler(lv_event_t *e)
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

static void screen_list_1_item2_event_handler(lv_event_t *e)
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

static void screen_list_1_item3_event_handler(lv_event_t *e)
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

// 声明外部变量
extern float latitude;
extern float longitude;

// 同步位置屏幕事件处理函数
void sync_location_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    
    if (!obj) {
        return;  // 静默返回，不打印错误
    }

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui) {
        return;  // 静默返回，不打印错误
    }

    switch (code) {
        case LV_EVENT_SCREEN_LOADED:
            // 屏幕加载完成时的处理
            ESP_LOGI(TAG, "Sync location screen loaded");
            break;
            
        case LV_EVENT_GESTURE:
        {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
            if (dir == LV_DIR_RIGHT) {
                // 向右滑动返回主屏幕
                ESP_LOGI(TAG, "Right swipe detected, returning to main screen");
                if (ui->screen) {
                    lv_scr_load_anim(ui->screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
                }
            }
            break;
        }
        default:
            break;
    }
}

// 同步位置列表项0事件处理函数
void sync_location_item0_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED) {
        return;
    }

    lv_obj_t *obj = lv_event_get_target(e);
    if (!obj) {
        return;  // 静默返回，不打印错误
    }

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui) {
        return;  // 静默返回，不打印错误
    }

    // 移除事件监听器，防止重复触发
    lv_obj_remove_event_cb(obj, sync_location_item0_event_handler);

    // 处理列表项0的点击事件
    ESP_LOGI(TAG, "Sync location item0 clicked");
    // 设置深圳经纬度
    latitude = 22.3349f;
    longitude = 114.1036f;
    
    // 返回主屏幕
    if (ui->screen) {
        lv_scr_load_anim(ui->screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
    }
}

// 同步位置列表项1事件处理函数
void sync_location_item1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED) {
        return;
    }

    lv_obj_t *obj = lv_event_get_target(e);
    if (!obj) {
        return;  // 静默返回，不打印错误
    }

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui) {
        return;  // 静默返回，不打印错误
    }

    // 移除事件监听器，防止重复触发
    lv_obj_remove_event_cb(obj, sync_location_item1_event_handler);

    // 处理列表项1的点击事件
    ESP_LOGI(TAG, "Sync location item1 clicked");
    // 设置哈尔滨经纬度
    latitude = 45.4915f;
    longitude = 126.3848f;
    
    // 返回主屏幕
    if (ui->screen) {
        lv_scr_load_anim(ui->screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
    }
}

// 同步位置列表项2事件处理函数
void sync_location_item2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED) {
        return;
    }

    lv_obj_t *obj = lv_event_get_target(e);
    if (!obj) {
        return;  // 静默返回，不打印错误
    }

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui) {
        return;  // 静默返回，不打印错误
    }

    // 移除事件监听器，防止重复触发
    lv_obj_remove_event_cb(obj, sync_location_item2_event_handler);

    // 处理列表项2的点击事件
    ESP_LOGI(TAG, "Sync location item2 clicked");
    // TODO: 实现GPS定位功能
    
    // 返回主屏幕
    if (ui->screen) {
        lv_scr_load_anim(ui->screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
    }
}

// 同步位置返回按钮事件处理函数
void sync_location_back_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_t *screen = lv_obj_get_screen(obj);
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);

    if (code == LV_EVENT_CLICKED) {
        // 处理返回按钮的点击事件
        ESP_LOGI(TAG, "Sync location back button clicked");
        lv_scr_load_anim(ui->screen, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, false);
    }
}

// 修改主屏幕的GPS更新按钮事件处理
static void screen_list_1_item4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        // 切换到位置同步屏幕
        setup_scr_sync_location(&guider_ui);
        lv_scr_load(guider_ui.sync_location_screen);
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
            // 发送停止跟踪通知到轨道跟踪任务
            if (orbit_trking_handler != NULL) {
                ESP_LOGI(TAG, "Sending tracking stop notification from orbit screen");
                xTaskNotify(orbit_trking_handler, END_ORB_TRKING, eSetValueWithOverwrite);
                ESP_LOGI(TAG, "Tracking stop notification sent from orbit screen");
            }
            
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

static void sat_param_screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
        // 屏幕加载时，使用缓存参数更新界面
        update_sat_param_on_screen_load();
        break;
        
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            // 发送停止跟踪通知到轨道跟踪任务
            if (orbit_trking_handler != NULL) {
                ESP_LOGI(TAG, "Sending tracking stop notification");
                xTaskNotify(orbit_trking_handler, END_ORB_TRKING, eSetValueWithOverwrite);
                ESP_LOGI(TAG, "Tracking stop notification sent");
            }
            
            // 向右滑动返回轨道跟踪屏幕
            lv_scr_load_anim(guider_ui.orbit_tracking_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, false);
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

void update_sat_param_screen(lv_ui *ui, const char* sat_name, double elevation, double azimuth, 
                           double range, double velocity, const char* status)
{
    // 每个值使用独立的静态缓冲区
    static char ele_buf[32];
    static char azi_buf[32];
    static char range_buf[32];
    static char vel_buf[32];
    static char time_buf[64];
    
    // 更新卫星名称
    if (ui->sat_name_label) {
        lv_label_set_text(ui->sat_name_label, sat_name);
    }
    
    // 使用ASCII文本"d"代替度数符号
    if (ui->elevation_value) {
        snprintf(ele_buf, sizeof(ele_buf), "%6.1f d", elevation);
        lv_label_set_text(ui->elevation_value, ele_buf);
    }
    
    if (ui->azimuth_value) {
        snprintf(azi_buf, sizeof(azi_buf), "%6.1f d", azimuth);
        lv_label_set_text(ui->azimuth_value, azi_buf);
    }
    
    // 确保空间足够显示完整的范围值
    if (ui->range_value) {
        snprintf(range_buf, sizeof(range_buf), "%6.1f km", range);
        lv_label_set_text(ui->range_value, range_buf);
    }
    
    // 确保空间足够显示完整的速度值
    if (ui->velocity_value) {
        snprintf(vel_buf, sizeof(vel_buf), "%6.3f km/s", velocity);
        lv_label_set_text(ui->velocity_value, vel_buf);
    }
    
    // 更新状态值
    if (ui->status_value) {
        lv_label_set_text(ui->status_value, status);
    }
    
    // 更新方向指示点位置
    if (ui->direction_point) {
        // 计算点在圆上的位置
        // 方位角是从北方顺时针计算的，需要转换为标准坐标系
        float angle_rad = (90.0 - azimuth) * 3.14159265 / 180.0;
        
        // 仰角决定距离圆心的距离 (90度对应圆心，0度或更小对应圆周)
        float elev_normalized = (elevation < 0) ? 0 : (elevation > 90) ? 90 : elevation;
        float distance = (90.0 - elev_normalized) / 90.0 * 70.0;  // 70是圆的半径
        
        // 计算坐标 (圆心是75,75)
        int x = 75 + (int)(cos(angle_rad) * distance);
        int y = 75 - (int)(sin(angle_rad) * distance);
        
        // 点的尺寸是10x10，所以调整位置使其中心对准计算的坐标
        lv_obj_set_pos(ui->direction_point, x - 5, y - 5);
    }
    
    // 更新最后一次更新时间
    if (ui->update_time_label) {
        // 获取当前时间
        time_t now;
        struct tm timeinfo;
        time(&now);
        localtime_r(&now, &timeinfo);
        
        snprintf(time_buf, sizeof(time_buf), "Updated: %02d:%02d:%02d", 
                 timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        lv_label_set_text(ui->update_time_label, time_buf);
    }
}

// 修改卫星列表项点击事件处理
static void satellite_item_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    
    if (code == LV_EVENT_CLICKED) {
        ESP_LOGI(TAG, "Satellite item clicked");
        // 获取被点击的列表项索引
        for (int i = 0; i < 10; i++) {
            if (target == guider_ui.satellite_items[i]) {
                // 获取卫星名称
                const char* sat_name = lv_list_get_btn_text(guider_ui.satellite_list, target);
                ESP_LOGI(TAG, "Selected satellite: %s", sat_name);
                
                // 先发送开始跟踪通知到轨道跟踪任务
                if (orbit_trking_handler != NULL) {
                    ESP_LOGI(TAG, "Sending tracking start notification");
                    xTaskNotify(orbit_trking_handler, START_ORB_TRKING, eSetValueWithOverwrite);
                    ESP_LOGI(TAG, "Tracking start notification sent");
                    
                    // 给轨道跟踪任务一些时间进入接收卫星名称的状态
                    vTaskDelay(pdMS_TO_TICKS(100));
                } else {
                    ESP_LOGE(TAG, "orbit_trking_handler is NULL");
                    return;
                }
                
                // 发送卫星名称到跟踪任务
                if (SatnameQueueHandler != NULL) {
                    ESP_LOGI(TAG, "Sending satellite name to queue");
                    BaseType_t xStatus = xQueueSend(SatnameQueueHandler, sat_name, pdMS_TO_TICKS(100));
                    if (xStatus != pdPASS) {
                        ESP_LOGE(TAG, "Failed to send satellite name to queue");
                        return;
                    }
                    ESP_LOGI(TAG, "Satellite name sent to queue successfully");
                } else {
                    ESP_LOGE(TAG, "SatnameQueueHandler is NULL");
                    return;
                }
                
                // 确保参数显示屏幕已创建
                if (guider_ui.sat_param_screen == NULL) {
                    setup_scr_sat_param(&guider_ui);
                }
                
                // 确保事件处理函数已注册
                lv_obj_add_event_cb(guider_ui.sat_param_screen, sat_param_screen_event_handler, LV_EVENT_ALL, NULL);
                
                // 更新参数显示（这里使用示例数据，实际应该从卫星跟踪系统获取）
                // update_sat_param_screen(&guider_ui, sat_name, 45.0, 180.0, 1000.0, 7.8, "In View");
                
                // 加载参数显示屏幕
                lv_scr_load_anim(guider_ui.sat_param_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
                break;
            }
        }
    }
}

void events_init_screen(lv_ui *ui)
{
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
    if (ui->orbit_tracking_screen != NULL) {
        lv_obj_add_event_cb(ui->orbit_tracking_screen, orbit_tracking_screen_event_handler, LV_EVENT_ALL, ui);
    }

    for (int i = 0; i < 10; i++) {
        if (ui->satellite_items[i] != NULL) {
            lv_obj_add_event_cb(ui->satellite_items[i], satellite_item_event_handler, LV_EVENT_CLICKED, NULL);
        }
    }
}

void events_init_sync_location(lv_ui *ui)
{
    if (!ui) {
        return;  // 静默返回，不打印错误
    }

    // 为屏幕添加事件处理
    if (ui->sync_location_screen) {
        // 先移除可能存在的旧事件处理函数
        lv_obj_remove_event_cb(ui->sync_location_screen, sync_location_screen_event_handler);
        // 只注册一次事件处理函数
        lv_obj_add_event_cb(ui->sync_location_screen, sync_location_screen_event_handler, LV_EVENT_SCREEN_LOADED | LV_EVENT_GESTURE, ui);
    }
    
    // 为列表项添加事件处理
    if (ui->sync_location_item0) {
        lv_obj_remove_event_cb(ui->sync_location_item0, sync_location_item0_event_handler);
        lv_obj_add_event_cb(ui->sync_location_item0, sync_location_item0_event_handler, LV_EVENT_CLICKED, ui);
    }
    
    if (ui->sync_location_item1) {
        lv_obj_remove_event_cb(ui->sync_location_item1, sync_location_item1_event_handler);
        lv_obj_add_event_cb(ui->sync_location_item1, sync_location_item1_event_handler, LV_EVENT_CLICKED, ui);
    }
    
    if (ui->sync_location_item2) {
        lv_obj_remove_event_cb(ui->sync_location_item2, sync_location_item2_event_handler);
        lv_obj_add_event_cb(ui->sync_location_item2, sync_location_item2_event_handler, LV_EVENT_CLICKED, ui);
    }
    
    // 为返回按钮添加事件处理
    if (ui->sync_location_back_btn) {
        lv_obj_add_event_cb(ui->sync_location_back_btn, sync_location_back_btn_event_handler, LV_EVENT_CLICKED, ui);
    }
}

void events_init(lv_ui *ui)
{
    events_init_screen(ui);
    
    if (ui->orbit_tracking_screen != NULL) {
        events_init_orbit_tracking(ui);
    }
}
