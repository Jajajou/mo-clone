#pragma once
#include <lvgl.h>

// Khởi động toàn bộ UI
void dashboard_init();

// Cập nhật giá trị hiển thị
void dashboard_set_speed(int kmh);
void dashboard_set_rpm(int rpm);
void dashboard_set_gps(float lat, float lng);
void dashboard_set_turn_left(bool active);
void dashboard_set_turn_right(bool active);
void dashboard_set_headlight(bool high_beam);
void dashboard_show_notification(const char* title, const char* body);
