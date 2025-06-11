/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_cont_1;
	lv_obj_t *screen_list_1;
	lv_obj_t *screen_list_1_item0;
	lv_obj_t *screen_list_1_item1;
	lv_obj_t *screen_list_1_item2;
	lv_obj_t *screen_list_1_item3;
	lv_obj_t *screen_list_1_item4;
	lv_obj_t *screen_list_1_item5;
	lv_obj_t *screen_cont_2;
	lv_obj_t *screen_img_1;
	lv_obj_t *screen_label_1;

	// Orbit tracking screen
	lv_obj_t *orbit_tracking_screen;
	bool orbit_tracking_screen_del;
	lv_obj_t *orbit_tracking_cont;
	lv_obj_t *orbit_tracking_img;
	lv_obj_t *orbit_tracking_label;
	
	// Satellite list
	lv_obj_t *satellite_list;
	lv_obj_t *satellite_list_cont;
	lv_obj_t *satellite_items[10];  // 存储10个卫星列表项

	// Satellite parameter screen
	lv_obj_t *sat_param_screen;     // 卫星参数显示屏幕
	lv_obj_t *sat_param_cont;       // 参数显示容器
	lv_obj_t *sat_param_title;      // 标题
	lv_obj_t *sat_name_label;       // 卫星名称
	lv_obj_t *elevation_label;      // 俯仰角标签
	lv_obj_t *elevation_value;      // 俯仰角数值
	lv_obj_t *azimuth_label;        // 方位角标签
	lv_obj_t *azimuth_value;        // 方位角数值
	lv_obj_t *range_label;          // 距离标签
	lv_obj_t *range_value;          // 距离数值
	lv_obj_t *velocity_label;       // 速度标签
	lv_obj_t *velocity_value;       // 速度数值
	lv_obj_t *status_label;         // 状态标签
	lv_obj_t *status_value;         // 状态数值

	// Sync location screen
	lv_obj_t *sync_location_screen;
	bool sync_location_screen_del;
	lv_obj_t *sync_location_cont;
	lv_obj_t *sync_location_list;
	lv_obj_t *sync_location_item0;  // 深圳
	lv_obj_t *sync_location_item1;  // 哈尔滨
	lv_obj_t *sync_location_item2;  // GPS定位
	lv_obj_t *sync_location_back_btn;
    
    // 新添加的元素
    lv_obj_t *utc_label;
    lv_obj_t *utc_value;
    
    lv_obj_t *date_label;
    lv_obj_t *date_value;

	lv_obj_t *direction_point;     // 方向指示点
    lv_obj_t *update_time_label;   // 更新时间标签
    
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;


void setup_scr_screen(lv_ui *ui);
void setup_scr_orbit_tracking(lv_ui *ui);
void setup_scr_sat_param(lv_ui *ui);
void update_sat_param_screen(lv_ui *ui, const char* sat_name, double elevation, double azimuth, 
                           double range, double velocity, const char* status);
void setup_scr_sync_location(lv_ui *ui);
void update_location_coordinates(float lat, float lon);
LV_IMG_DECLARE(_orbit_alpha_60x60);
LV_IMG_DECLARE(_time_alpha_60x60);
LV_IMG_DECLARE(_file_search_alpha_60x60);
LV_IMG_DECLARE(_download_alpha_60x60);
LV_IMG_DECLARE(_sat_alpha_64x64);
LV_IMG_DECLARE(_eph_grey_alpha_60x60);

LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_NotoSans_VariableFont_wdth_wght_24)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_customer_font_montserratMedium_20)

#ifdef __cplusplus
}
#endif
#endif
