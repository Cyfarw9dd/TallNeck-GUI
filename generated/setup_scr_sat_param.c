#include "gui_guider.h"
#include "lvgl.h"
#include "widgets_init.h"
#include "events_init.h"
#include "globals.h"  
#include "lvgl_display.h"

void setup_scr_sat_param(lv_ui *ui)
{
    // 如果屏幕已经存在，先删除它
    if (ui->sat_param_screen != NULL) {
        lv_obj_del(ui->sat_param_screen);
        ui->sat_param_screen = NULL;
    }
    
    // Create satellite parameter screen
    ui->sat_param_screen = lv_obj_create(NULL);
    if (ui->sat_param_screen == NULL) {
        return;
    }
    
    lv_obj_set_size(ui->sat_param_screen, 240, 536);
    lv_obj_set_scrollbar_mode(ui->sat_param_screen, LV_SCROLLBAR_MODE_OFF);

    // Create main container
    ui->sat_param_cont = lv_obj_create(ui->sat_param_screen);
    if (ui->sat_param_cont == NULL) {
        lv_obj_del(ui->sat_param_screen);
        ui->sat_param_screen = NULL;
        return;
    }
    
    lv_obj_set_size(ui->sat_param_cont, 240, 536);
    lv_obj_set_pos(ui->sat_param_cont, 0, 0);
    lv_obj_set_scrollbar_mode(ui->sat_param_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui->sat_param_cont, LV_DIR_NONE);  // 禁止所有方向的滚动
    
    // Set container style
    lv_obj_set_style_bg_color(ui->sat_param_cont, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sat_param_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sat_param_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // Create title
    ui->sat_param_title = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->sat_param_title, 0, 10);
    lv_obj_set_size(ui->sat_param_title, 240, 30);
    lv_label_set_text(ui->sat_param_title, "Satellite Parameters");
    lv_obj_set_style_text_align(ui->sat_param_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->sat_param_title, &lv_font_NotoSans_VariableFont_wdth_wght_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // Create satellite name
    ui->sat_name_label = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->sat_name_label, 20, 60);
    lv_obj_set_size(ui->sat_name_label, 200, 30);
    lv_label_set_text(ui->sat_name_label, "Satellite Name");
    lv_obj_set_style_text_font(ui->sat_name_label, &lv_font_NotoSans_VariableFont_wdth_wght_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // Create elevation parameter
    ui->elevation_label = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->elevation_label, 20, 120);
    lv_obj_set_size(ui->elevation_label, 100, 30);
    lv_label_set_text(ui->elevation_label, "Elevation:");
    
    ui->elevation_value = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->elevation_value, 130, 120);
    lv_obj_set_size(ui->elevation_value, 90, 30);
    lv_label_set_text(ui->elevation_value, "0.0°");
    
    // Create azimuth parameter
    ui->azimuth_label = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->azimuth_label, 20, 160);
    lv_obj_set_size(ui->azimuth_label, 100, 30);
    lv_label_set_text(ui->azimuth_label, "Azimuth:");
    
    ui->azimuth_value = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->azimuth_value, 130, 160);
    lv_obj_set_size(ui->azimuth_value, 90, 30);
    lv_label_set_text(ui->azimuth_value, "0.0°");
    
    // Create range parameter
    ui->range_label = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->range_label, 20, 200);
    lv_obj_set_size(ui->range_label, 100, 30);
    lv_label_set_text(ui->range_label, "Range:");
    
    ui->range_value = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->range_value, 130, 200);
    lv_obj_set_size(ui->range_value, 90, 30);
    lv_label_set_text(ui->range_value, "0.0 km");
    
    // Create velocity parameter
    ui->velocity_label = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->velocity_label, 20, 240);
    lv_obj_set_size(ui->velocity_label, 100, 30);
    lv_label_set_text(ui->velocity_label, "Velocity:");
    
    ui->velocity_value = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->velocity_value, 130, 240);
    lv_obj_set_size(ui->velocity_value, 90, 30);
    lv_label_set_text(ui->velocity_value, "0.0 km/s");
    
    // Create status parameter
    ui->status_label = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->status_label, 20, 280);
    lv_obj_set_size(ui->status_label, 100, 30);
    lv_label_set_text(ui->status_label, "Status:");
    
    ui->status_value = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->status_value, 130, 280);
    lv_obj_set_size(ui->status_value, 90, 30);
    lv_label_set_text(ui->status_value, "Unknown");
    
    // Set common style for parameter labels
    lv_obj_t* labels[] = {
        ui->elevation_label, ui->azimuth_label, ui->range_label,
        ui->velocity_label, ui->status_label
    };
    
    for(int i = 0; i < sizeof(labels)/sizeof(labels[0]); i++) {
        lv_obj_set_style_text_font(labels[i], &lv_font_NotoSans_VariableFont_wdth_wght_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    }
    
    // Set common style for value labels
    lv_obj_t* values[] = {
        ui->elevation_value, ui->azimuth_value, ui->range_value,
        ui->velocity_value, ui->status_value
    };
    
    for(int i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
        lv_obj_set_style_text_font(values[i], &lv_font_NotoSans_VariableFont_wdth_wght_24, LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(values[i], lv_color_hex(0x0000FF), LV_PART_MAIN|LV_STATE_DEFAULT);
    }
}