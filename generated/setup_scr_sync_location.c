#include "gui_guider.h"
#include "lvgl.h"
#include "widgets_init.h"
#include "events_init.h"

void setup_scr_sync_location(lv_ui *ui)
{
    // 如果屏幕已经存在，先删除它
    if (ui->sync_location_screen != NULL) {
        lv_obj_del(ui->sync_location_screen);
        ui->sync_location_screen = NULL;
    }
    
    // Create sync location screen
    ui->sync_location_screen = lv_obj_create(NULL);
    if (ui->sync_location_screen == NULL) {
        return;
    }
    
    lv_obj_set_size(ui->sync_location_screen, 240, 536);
    lv_obj_set_scrollbar_mode(ui->sync_location_screen, LV_SCROLLBAR_MODE_OFF);

    // Create main container
    ui->sync_location_cont = lv_obj_create(ui->sync_location_screen);
    if (ui->sync_location_cont == NULL) {
        lv_obj_del(ui->sync_location_screen);
        ui->sync_location_screen = NULL;
        return;
    }
    
    lv_obj_set_size(ui->sync_location_cont, 240, 536);
    lv_obj_set_pos(ui->sync_location_cont, 0, 0);
    lv_obj_set_scrollbar_mode(ui->sync_location_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui->sync_location_cont, LV_DIR_NONE);
    
    // Set container style
    lv_obj_set_style_bg_color(ui->sync_location_cont, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sync_location_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sync_location_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // Create list
    ui->sync_location_list = lv_list_create(ui->sync_location_cont);
    lv_obj_set_size(ui->sync_location_list, 240, 360);
    lv_obj_set_pos(ui->sync_location_list, 0, 80);
    lv_obj_set_scrollbar_mode(ui->sync_location_list, LV_SCROLLBAR_MODE_ACTIVE);
    
    // Create list items
    ui->sync_location_item0 = lv_list_add_btn(ui->sync_location_list, LV_SYMBOL_GPS, "Shenzhen (22.3349, 114.1036)");
    ui->sync_location_item1 = lv_list_add_btn(ui->sync_location_list, LV_SYMBOL_GPS, "Harbin (45.4915, 126.3848)");
    ui->sync_location_item2 = lv_list_add_btn(ui->sync_location_list, LV_SYMBOL_GPS, "Use GPS Location");
    
    // Create back button
    ui->sync_location_back_btn = lv_btn_create(ui->sync_location_cont);
    lv_obj_set_size(ui->sync_location_back_btn, 100, 40);
    lv_obj_align(ui->sync_location_back_btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_t *back_label = lv_label_create(ui->sync_location_back_btn);
    lv_label_set_text(back_label, "Back");
    lv_obj_center(back_label);
    
    // Add event handlers
    lv_obj_add_event_cb(ui->sync_location_screen, sync_location_screen_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->sync_location_item0, sync_location_item0_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui->sync_location_item1, sync_location_item1_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui->sync_location_item2, sync_location_item2_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui->sync_location_back_btn, sync_location_back_btn_event_handler, LV_EVENT_CLICKED, NULL);
} 