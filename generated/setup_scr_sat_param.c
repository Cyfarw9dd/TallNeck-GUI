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
    
    // 创建卫星参数屏幕
    ui->sat_param_screen = lv_obj_create(NULL);
    if (ui->sat_param_screen == NULL) {
        return;
    }
    
    // 设置屏幕尺寸和滚动模式
    lv_obj_set_size(ui->sat_param_screen, 240, 536);
    lv_obj_set_scrollbar_mode(ui->sat_param_screen, LV_SCROLLBAR_MODE_OFF);

    // 创建主容器
    ui->sat_param_cont = lv_obj_create(ui->sat_param_screen);
    if (ui->sat_param_cont == NULL) {
        lv_obj_del(ui->sat_param_screen);
        ui->sat_param_screen = NULL;
        return;
    }
    
    // 设置容器属性
    lv_obj_set_size(ui->sat_param_cont, 240, 536);
    lv_obj_set_pos(ui->sat_param_cont, 0, 0);
    lv_obj_set_scrollbar_mode(ui->sat_param_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui->sat_param_cont, LV_DIR_NONE);
    lv_obj_set_style_pad_all(ui->sat_param_cont, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // 设置容器样式
    lv_obj_set_style_bg_color(ui->sat_param_cont, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sat_param_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sat_param_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // 创建标题
    ui->sat_param_title = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->sat_param_title, 0, 15);
    lv_obj_set_size(ui->sat_param_title, 240, 35);
    lv_label_set_text(ui->sat_param_title, "Satellite Parameters");
    lv_obj_set_style_text_align(ui->sat_param_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->sat_param_title, &lv_font_NotoSans_VariableFont_wdth_wght_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sat_param_title, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // 创建水平分隔线
    lv_obj_t *separator = lv_line_create(ui->sat_param_cont);
    static lv_point_t line_points[] = {{10, 0}, {220, 0}};
    lv_line_set_points(separator, line_points, 2);
    lv_obj_set_pos(separator, 10, 60);
    lv_obj_set_style_line_width(separator, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(separator, lv_color_hex(0xCCCCCC), LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // 创建卫星名称标签
    ui->sat_name_label = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->sat_name_label, 20, 70);
    lv_obj_set_size(ui->sat_name_label, 200, 30);
    lv_label_set_text(ui->sat_name_label, "Satellite Name");
    lv_obj_set_style_text_font(ui->sat_name_label, &lv_font_NotoSans_VariableFont_wdth_wght_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sat_name_label, lv_color_hex(0x003366), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->sat_name_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // 创建参数区域面板
    lv_obj_t *params_panel = lv_obj_create(ui->sat_param_cont);
    lv_obj_set_pos(params_panel, 10, 110);
    lv_obj_set_size(params_panel, 220, 230);
    lv_obj_set_style_bg_color(params_panel, lv_color_hex(0xF8F8F8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(params_panel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(params_panel, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(params_panel, lv_color_hex(0xDDDDDD), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(params_panel, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(params_panel, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(params_panel, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(params_panel, 40, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(params_panel, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // 定义面板内标签和值的位置参数
    int label_x = 10;
    int value_x = 95;  // 调整值标签起始位置，给更多显示空间
    int row_height = 40;
    int start_y = 10;
    
    // 创建仰角参数
    ui->elevation_label = lv_label_create(params_panel);
    lv_obj_set_pos(ui->elevation_label, label_x, start_y);
    lv_obj_set_size(ui->elevation_label, 75, 30);
    lv_label_set_text(ui->elevation_label, "Ele:");
    
    ui->elevation_value = lv_label_create(params_panel);
    lv_obj_set_pos(ui->elevation_value, value_x, start_y);
    lv_obj_set_size(ui->elevation_value, 110, 30);  // 增加宽度
    lv_label_set_text(ui->elevation_value, "0.0 d");
    lv_obj_set_style_text_align(ui->elevation_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_label_set_long_mode(ui->elevation_value, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_anim_time(ui->elevation_value, 2000, LV_PART_MAIN|LV_STATE_DEFAULT);  // 设置滚动速度
    
    // 创建方位角参数
    ui->azimuth_label = lv_label_create(params_panel);
    lv_obj_set_pos(ui->azimuth_label, label_x, start_y + row_height);
    lv_obj_set_size(ui->azimuth_label, 75, 30);
    lv_label_set_text(ui->azimuth_label, "Azi:");
    
    ui->azimuth_value = lv_label_create(params_panel);
    lv_obj_set_pos(ui->azimuth_value, value_x, start_y + row_height);
    lv_obj_set_size(ui->azimuth_value, 110, 30);  // 增加宽度
    lv_label_set_text(ui->azimuth_value, "0.0 d");
    lv_obj_set_style_text_align(ui->azimuth_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_label_set_long_mode(ui->azimuth_value, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_anim_time(ui->azimuth_value, 2000, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // 创建距离参数
    ui->range_label = lv_label_create(params_panel);
    lv_obj_set_pos(ui->range_label, label_x, start_y + 2*row_height);
    lv_obj_set_size(ui->range_label, 75, 30);
    lv_label_set_text(ui->range_label, "Range:");
    
    ui->range_value = lv_label_create(params_panel);
    lv_obj_set_pos(ui->range_value, value_x, start_y + 2*row_height);
    lv_obj_set_size(ui->range_value, 110, 30);  // 增加宽度
    lv_label_set_text(ui->range_value, "0.0 km");
    lv_obj_set_style_text_align(ui->range_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_label_set_long_mode(ui->range_value, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_anim_time(ui->range_value, 2000, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_anim_delay(ui->range_value, 500, LV_PART_MAIN|LV_STATE_DEFAULT);  // 设置滚动延迟
    
    // 创建速度参数
    ui->velocity_label = lv_label_create(params_panel);
    lv_obj_set_pos(ui->velocity_label, label_x, start_y + 3*row_height);
    lv_obj_set_size(ui->velocity_label, 75, 30);
    lv_label_set_text(ui->velocity_label, "Vel:");  // 缩短标签文本
    
    ui->velocity_value = lv_label_create(params_panel);
    lv_obj_set_pos(ui->velocity_value, value_x, start_y + 3*row_height);
    lv_obj_set_size(ui->velocity_value, 110, 30);  // 增加宽度
    lv_label_set_text(ui->velocity_value, "0.0 km/s");
    lv_obj_set_style_text_align(ui->velocity_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_label_set_long_mode(ui->velocity_value, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_anim_time(ui->velocity_value, 2000, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_anim_delay(ui->velocity_value, 500, LV_PART_MAIN|LV_STATE_DEFAULT);  // 设置滚动延迟
    
    // 创建状态参数
    ui->status_label = lv_label_create(params_panel);
    lv_obj_set_pos(ui->status_label, label_x, start_y + 4*row_height);
    lv_obj_set_size(ui->status_label, 75, 30);
    lv_label_set_text(ui->status_label, "Status:");
    
    ui->status_value = lv_label_create(params_panel);
    lv_obj_set_pos(ui->status_value, value_x, start_y + 4*row_height);
    lv_obj_set_size(ui->status_value, 110, 30);  // 增加宽度
    lv_label_set_text(ui->status_value, "Unknown");
    lv_obj_set_style_text_align(ui->status_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_label_set_long_mode(ui->status_value, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_anim_time(ui->status_value, 2000, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_anim_delay(ui->status_value, 500, LV_PART_MAIN|LV_STATE_DEFAULT);  // 设置滚动延迟
    
    // 创建卫星位置指示面板
    lv_obj_t *direction_panel = lv_obj_create(ui->sat_param_cont);
    lv_obj_set_pos(direction_panel, 45, 350);
    lv_obj_set_size(direction_panel, 150, 150);
    lv_obj_set_style_radius(direction_panel, 75, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(direction_panel, lv_color_hex(0xF0F0FF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(direction_panel, 200, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(direction_panel, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(direction_panel, lv_color_hex(0xBBBBDD), LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // 添加方向标记（北、东、南、西）
    lv_obj_t *north_label = lv_label_create(direction_panel);
    lv_label_set_text(north_label, "N");
    lv_obj_set_pos(north_label, 70, 5);
    
    lv_obj_t *east_label = lv_label_create(direction_panel);
    lv_label_set_text(east_label, "E");
    lv_obj_set_pos(east_label, 135, 70);
    
    lv_obj_t *south_label = lv_label_create(direction_panel);
    lv_label_set_text(south_label, "S");
    lv_obj_set_pos(south_label, 70, 135);
    
    lv_obj_t *west_label = lv_label_create(direction_panel);
    lv_label_set_text(west_label, "W");
    lv_obj_set_pos(west_label, 5, 70);
    
    // 添加仰角圈（30°、60°）
    lv_obj_t *ele60_circle = lv_obj_create(direction_panel);
    lv_obj_set_pos(ele60_circle, 50, 50);
    lv_obj_set_size(ele60_circle, 50, 50);
    lv_obj_set_style_radius(ele60_circle, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ele60_circle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ele60_circle, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ele60_circle, lv_color_hex(0x999999), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ele60_circle, 100, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    lv_obj_t *ele30_circle = lv_obj_create(direction_panel);
    lv_obj_set_pos(ele30_circle, 25, 25);
    lv_obj_set_size(ele30_circle, 100, 100);
    lv_obj_set_style_radius(ele30_circle, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ele30_circle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ele30_circle, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ele30_circle, lv_color_hex(0x999999), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ele30_circle, 100, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // 创建方向指示点
    ui->direction_point = lv_obj_create(direction_panel);
    lv_obj_set_size(ui->direction_point, 10, 10);
    lv_obj_set_style_radius(ui->direction_point, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->direction_point, lv_color_hex(0x0000FF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->direction_point, 70, 70);  // 初始位置在圆心
    
    // 添加最后更新时间显示
    ui->update_time_label = lv_label_create(ui->sat_param_cont);
    lv_obj_set_pos(ui->update_time_label, 10, 510);
    lv_obj_set_size(ui->update_time_label, 220, 20);
    lv_obj_set_style_text_align(ui->update_time_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->update_time_label, lv_color_hex(0x999999), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->update_time_label, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_label_set_text(ui->update_time_label, "Waiting for data...");
    
    // 设置参数标签的共同样式
    lv_obj_t* labels[] = {
        ui->elevation_label, ui->azimuth_label, ui->range_label,
        ui->velocity_label, ui->status_label
    };
    
    for(int i = 0; i < sizeof(labels)/sizeof(labels[0]); i++) {
        lv_obj_set_style_text_font(labels[i], &lv_font_NotoSans_VariableFont_wdth_wght_24, LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(labels[i], lv_color_hex(0x333333), LV_PART_MAIN|LV_STATE_DEFAULT);
    }
    
    // 设置参数值的共同样式
    lv_obj_t* values[] = {
        ui->elevation_value, ui->azimuth_value, ui->range_value,
        ui->velocity_value, ui->status_value
    };
    
    for(int i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
        lv_obj_set_style_text_font(values[i], &lv_font_NotoSans_VariableFont_wdth_wght_24, LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(values[i], lv_color_hex(0x0066CC), LV_PART_MAIN|LV_STATE_DEFAULT);
        // 启用文本滚动所需的设置
        lv_obj_set_style_anim_time(values[i], 2000, LV_PART_MAIN|LV_STATE_DEFAULT);
        // 如果文本内容短于标签宽度，则不会滚动；如果超出才会滚动
    }
}