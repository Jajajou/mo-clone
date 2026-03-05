#include "dashboard.h"
#include <Adafruit_ILI9341.h>
#include <lvgl.h>
#include "../config.h"

// === Software SPI — không dùng hardware SPI peripheral ===
// Truyền đủ 6 tham số (cs, dc, mosi, sclk, rst, miso=-1) → bit-bang GPIO
// Hardware SPI của ESP32-S3 không được Wokwi simulate đúng cách
static Adafruit_ILI9341 tft(
    PIN_TFT_CS,
    PIN_TFT_DC,
    PIN_TFT_MOSI,
    PIN_TFT_SCLK,
    PIN_TFT_RST,
    -1   // MISO không cần
);

// === LVGL display buffer ===
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[240 * 10]; // Nhỏ hơn vì software SPI chậm hơn

// === UI objects ===
static lv_obj_t* scr;
static lv_obj_t* arc_speed;
static lv_obj_t* lbl_speed;
static lv_obj_t* lbl_unit;
static lv_obj_t* arc_rpm;
static lv_obj_t* lbl_rpm;
static lv_obj_t* lbl_turn_left;
static lv_obj_t* lbl_turn_right;
static lv_obj_t* lbl_beam;
static lv_obj_t* lbl_notify;

// === LVGL flush callback ===
static void tft_flush(lv_disp_drv_t* drv, const lv_area_t* area, lv_color_t* color_map) {
    uint16_t w = area->x2 - area->x1 + 1;
    uint16_t h = area->y2 - area->y1 + 1;
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.writePixels((uint16_t*)color_map, w * h);
    tft.endWrite();
    lv_disp_flush_ready(drv);
}

static void build_ui() {
    scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);

    // Vòng cung tốc độ (ngoài)
    arc_speed = lv_arc_create(scr);
    lv_obj_set_size(arc_speed, 220, 220);
    lv_obj_center(arc_speed);
    lv_arc_set_rotation(arc_speed, 135);
    lv_arc_set_bg_angles(arc_speed, 0, 270);
    lv_arc_set_value(arc_speed, 0);
    lv_arc_set_range(arc_speed, 0, MAX_SPEED_KMH);
    lv_obj_set_style_arc_color(arc_speed, lv_color_hex(0x00BFFF), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(arc_speed, 12, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc_speed, lv_color_hex(0x222222), LV_PART_MAIN);
    lv_obj_set_style_arc_width(arc_speed, 12, LV_PART_MAIN);
    lv_obj_remove_style(arc_speed, NULL, LV_PART_KNOB);

    // Vòng cung RPM (trong)
    arc_rpm = lv_arc_create(scr);
    lv_obj_set_size(arc_rpm, 160, 160);
    lv_obj_center(arc_rpm);
    lv_arc_set_rotation(arc_rpm, 135);
    lv_arc_set_bg_angles(arc_rpm, 0, 270);
    lv_arc_set_value(arc_rpm, 0);
    lv_arc_set_range(arc_rpm, 0, MAX_RPM);
    lv_obj_set_style_arc_color(arc_rpm, lv_color_hex(0xFF4500), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(arc_rpm, 6, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc_rpm, lv_color_hex(0x1A1A1A), LV_PART_MAIN);
    lv_obj_set_style_arc_width(arc_rpm, 6, LV_PART_MAIN);
    lv_obj_remove_style(arc_rpm, NULL, LV_PART_KNOB);

    // Số tốc độ
    lbl_speed = lv_label_create(scr);
    lv_label_set_text(lbl_speed, "0");
    lv_obj_set_style_text_font(lbl_speed, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(lbl_speed, lv_color_white(), 0);
    lv_obj_align(lbl_speed, LV_ALIGN_CENTER, 0, -10);

    lbl_unit = lv_label_create(scr);
    lv_label_set_text(lbl_unit, "km/h");
    lv_obj_set_style_text_font(lbl_unit, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(lbl_unit, lv_color_hex(0x888888), 0);
    lv_obj_align(lbl_unit, LV_ALIGN_CENTER, 0, 30);

    // RPM label
    lbl_rpm = lv_label_create(scr);
    lv_label_set_text(lbl_rpm, "0 rpm");
    lv_obj_set_style_text_font(lbl_rpm, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(lbl_rpm, lv_color_hex(0xFF4500), 0);
    lv_obj_align(lbl_rpm, LV_ALIGN_CENTER, 0, 50);

    // Xi nhan trái
    lbl_turn_left = lv_label_create(scr);
    lv_label_set_text(lbl_turn_left, "<");
    lv_obj_set_style_text_font(lbl_turn_left, &lv_font_montserrat_28, 0);
    lv_obj_set_style_text_color(lbl_turn_left, lv_color_hex(0x333333), 0);
    lv_obj_align(lbl_turn_left, LV_ALIGN_LEFT_MID, 15, 0);

    // Xi nhan phải
    lbl_turn_right = lv_label_create(scr);
    lv_label_set_text(lbl_turn_right, ">");
    lv_obj_set_style_text_font(lbl_turn_right, &lv_font_montserrat_28, 0);
    lv_obj_set_style_text_color(lbl_turn_right, lv_color_hex(0x333333), 0);
    lv_obj_align(lbl_turn_right, LV_ALIGN_RIGHT_MID, -15, 0);

    // Đèn pha
    lbl_beam = lv_label_create(scr);
    lv_label_set_text(lbl_beam, "HI");
    lv_obj_set_style_text_font(lbl_beam, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(lbl_beam, lv_color_hex(0x333333), 0);
    lv_obj_align(lbl_beam, LV_ALIGN_TOP_MID, 0, 20);

    // Thông báo
    lbl_notify = lv_label_create(scr);
    lv_label_set_text(lbl_notify, "");
    lv_obj_set_style_text_font(lbl_notify, &lv_font_montserrat_10, 0);
    lv_obj_set_style_text_color(lbl_notify, lv_color_hex(0xAAAAAA), 0);
    lv_label_set_long_mode(lbl_notify, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(lbl_notify, 200);
    lv_obj_align(lbl_notify, LV_ALIGN_BOTTOM_MID, 0, -15);
}

void dashboard_init() {
    tft.begin();              // Software SPI init — không bao giờ treo
    tft.setRotation(0);
    tft.fillScreen(ILI9341_RED);   // Nếu thấy đỏ → OK
    delay(300);
    tft.fillScreen(ILI9341_BLACK);

    pinMode(PIN_TFT_BL, OUTPUT);
    digitalWrite(PIN_TFT_BL, HIGH); // Bật backlight

    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 240 * 10);

    static lv_disp_drv_t drv;
    lv_disp_drv_init(&drv);
    drv.hor_res  = 240;
    drv.ver_res  = 240;
    drv.flush_cb = tft_flush;
    drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&drv);

    build_ui();
}

void dashboard_set_speed(int kmh) {
    if (kmh < 0) kmh = 0;
    if (kmh > MAX_SPEED_KMH) kmh = MAX_SPEED_KMH;
    lv_arc_set_value(arc_speed, kmh);
    char buf[8];
    snprintf(buf, sizeof(buf), "%d", kmh);
    lv_label_set_text(lbl_speed, buf);
}

void dashboard_set_rpm(int rpm) {
    if (rpm < 0) rpm = 0;
    if (rpm > MAX_RPM) rpm = MAX_RPM;
    lv_arc_set_value(arc_rpm, rpm);
    char buf[12];
    snprintf(buf, sizeof(buf), "%d rpm", rpm);
    lv_label_set_text(lbl_rpm, buf);
}

void dashboard_set_gps(float lat, float lng) {
    (void)lat;
    (void)lng;
}

void dashboard_set_turn_left(bool active) {
    lv_color_t color = active ? lv_color_hex(0x00FF00) : lv_color_hex(0x333333);
    lv_obj_set_style_text_color(lbl_turn_left, color, 0);
}

void dashboard_set_turn_right(bool active) {
    lv_color_t color = active ? lv_color_hex(0x00FF00) : lv_color_hex(0x333333);
    lv_obj_set_style_text_color(lbl_turn_right, color, 0);
}

void dashboard_set_headlight(bool high_beam) {
    lv_color_t color = high_beam ? lv_color_hex(0x00BFFF) : lv_color_hex(0x333333);
    lv_obj_set_style_text_color(lbl_beam, color, 0);
    lv_label_set_text(lbl_beam, high_beam ? "HI" : "LO");
}

void dashboard_show_notification(const char* title, const char* body) {
    static char buf[64];
    snprintf(buf, sizeof(buf), "%s: %s", title, body);
    lv_label_set_text(lbl_notify, buf);
}
