#include "gui_guider.h"
#include "lvgl.h"
#include "widgets_init.h"
#include "events_init.h"

void setup_scr_orbit_tracking(lv_ui *ui)
{
    // 如果屏幕已经存在，先删除它
    if (ui->orbit_tracking_screen != NULL) {
        lv_obj_del(ui->orbit_tracking_screen);
        ui->orbit_tracking_screen = NULL;
    }
    
    // Create orbit tracking screen
    ui->orbit_tracking_screen = lv_obj_create(NULL);
    if (ui->orbit_tracking_screen == NULL) {
        return; // 如果创建失败，直接返回
    }
    
    lv_obj_set_size(ui->orbit_tracking_screen, 240, 536);
    lv_obj_set_scrollbar_mode(ui->orbit_tracking_screen, LV_SCROLLBAR_MODE_OFF);

    // Create container for logo and title
    ui->orbit_tracking_cont = lv_obj_create(ui->orbit_tracking_screen);
    if (ui->orbit_tracking_cont == NULL) {
        lv_obj_del(ui->orbit_tracking_screen);
        ui->orbit_tracking_screen = NULL;
        return;
    }
    
    lv_obj_set_pos(ui->orbit_tracking_cont, 0, 0);
    lv_obj_set_size(ui->orbit_tracking_cont, 240, 81);
    lv_obj_set_scrollbar_mode(ui->orbit_tracking_cont, LV_SCROLLBAR_MODE_OFF);

    // Set container style
    lv_obj_set_style_border_width(ui->orbit_tracking_cont, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->orbit_tracking_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->orbit_tracking_cont, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->orbit_tracking_cont, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->orbit_tracking_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->orbit_tracking_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->orbit_tracking_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->orbit_tracking_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->orbit_tracking_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->orbit_tracking_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    // Create logo image
    ui->orbit_tracking_img = lv_img_create(ui->orbit_tracking_screen);
    if (ui->orbit_tracking_img == NULL) {
        lv_obj_del(ui->orbit_tracking_screen);
        ui->orbit_tracking_screen = NULL;
        return;
    }
    
    lv_img_set_src(ui->orbit_tracking_img, &_sat_alpha_64x64);
    lv_img_set_pivot(ui->orbit_tracking_img, 50, 50);
    lv_img_set_angle(ui->orbit_tracking_img, 0);
    lv_obj_set_pos(ui->orbit_tracking_img, 16, 9);
    lv_obj_set_size(ui->orbit_tracking_img, 64, 64);

    // Set image style
    lv_obj_set_style_img_recolor_opa(ui->orbit_tracking_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->orbit_tracking_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->orbit_tracking_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->orbit_tracking_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    // Create title label
    ui->orbit_tracking_label = lv_label_create(ui->orbit_tracking_screen);
    if (ui->orbit_tracking_label == NULL) {
        lv_obj_del(ui->orbit_tracking_screen);
        ui->orbit_tracking_screen = NULL;
        return;
    }
    
    lv_label_set_text(ui->orbit_tracking_label, "TallNeck");
    lv_label_set_long_mode(ui->orbit_tracking_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->orbit_tracking_label, 89, 22);
    lv_obj_set_size(ui->orbit_tracking_label, 130, 46);

    // Set label style
    lv_obj_set_style_border_width(ui->orbit_tracking_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->orbit_tracking_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->orbit_tracking_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->orbit_tracking_label, &lv_font_NotoSans_VariableFont_wdth_wght_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->orbit_tracking_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->orbit_tracking_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->orbit_tracking_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->orbit_tracking_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->orbit_tracking_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->orbit_tracking_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->orbit_tracking_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    // Create satellite list container
    ui->satellite_list_cont = lv_obj_create(ui->orbit_tracking_screen);
    if (ui->satellite_list_cont == NULL) {
        lv_obj_del(ui->orbit_tracking_screen);
        ui->orbit_tracking_screen = NULL;
        return;
    }
    
    lv_obj_set_pos(ui->satellite_list_cont, 0, 81);
    lv_obj_set_size(ui->satellite_list_cont, 240, 455);
    lv_obj_set_scrollbar_mode(ui->satellite_list_cont, LV_SCROLLBAR_MODE_AUTO);
    
    // Set container style
    lv_obj_set_style_bg_opa(ui->satellite_list_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->satellite_list_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->satellite_list_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->satellite_list_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // Create satellite list
    ui->satellite_list = lv_list_create(ui->satellite_list_cont);
    if (ui->satellite_list == NULL) {
        lv_obj_del(ui->orbit_tracking_screen);
        ui->orbit_tracking_screen = NULL;
        return;
    }
    
    lv_obj_set_size(ui->satellite_list, 240, 455);
    lv_obj_set_style_bg_opa(ui->satellite_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->satellite_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->satellite_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    // Add satellite items
    const char* satellites[] = {
        "OSCAR 7 (AO-7)",
        "PHASE 3B (AO-10)",
        "UOSAT 2 (UO-11)",
        "LUSAT (LO-19)",
        "EYESAT A (AO-27)",
        "ITAMSAT (IO-26)",
        "RADIO ROSTO (RS-15)",
        "JAS-2 (FO-29)",
        "TECHSAT 1B (GO-32)",
        "ISS (ZARYA)"
    };
    
    for (int i = 0; i < 10; i++) {
        ui->satellite_items[i] = lv_list_add_btn(ui->satellite_list, NULL, satellites[i]);
        if (ui->satellite_items[i] != NULL) {
            lv_obj_set_style_text_font(ui->satellite_items[i], &lv_font_NotoSans_VariableFont_wdth_wght_24, LV_PART_MAIN|LV_STATE_DEFAULT);
            lv_obj_set_style_pad_all(ui->satellite_items[i], 15, LV_PART_MAIN|LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(ui->satellite_items[i], lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
        }
    }

    // Update current screen layout
    lv_obj_update_layout(ui->orbit_tracking_screen);
    
    // Initialize events for orbit tracking screen
    events_init_orbit_tracking(ui);
} 