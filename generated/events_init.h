/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "globals.h"

void events_init(lv_ui *ui);

void events_init_screen(lv_ui *ui);

void events_init_orbit_tracking(lv_ui *ui);

void events_init_sync_location(lv_ui *ui);

// 声明list_container_event_handler函数
void list_container_event_handler(lv_event_t *e);

// Sync location screen event handlers
void sync_location_screen_event_handler(lv_event_t *e);
void sync_location_item0_event_handler(lv_event_t *e);
void sync_location_item1_event_handler(lv_event_t *e);
void sync_location_item2_event_handler(lv_event_t *e);
void sync_location_back_btn_event_handler(lv_event_t *e);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
