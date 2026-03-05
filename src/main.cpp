#include <Arduino.h>
#include "config.h"
#include "ui/dashboard.h"
#include "sensors/gps_reader.h"
#include "sensors/rpm_reader.h"
#include "control/turn_signal.h"
#include "control/headlight.h"

// === MOCK DATA (chỉ dùng khi DEBUG_MOCK_DATA = true) ===
static float mockSpeed   = 0;
static int   mockRpm     = 0;
static bool  mockGoingUp = true;

void updateMockData() {
    // Mô phỏng tăng/giảm tốc độ và vòng tua
    if (mockGoingUp) {
        mockSpeed += 1.5f;
        mockRpm   += 150;
        if (mockSpeed >= 120) mockGoingUp = false;
    } else {
        mockSpeed -= 1.5f;
        mockRpm   -= 150;
        if (mockSpeed <= 0) mockGoingUp = true;
    }
}

void setup() {
    if (DEBUG_SERIAL) Serial.begin(115200);

    // Buttons & relay trước — nếu display treo thì nút vẫn hoạt động
    turn_signal_init();
    headlight_init();
    gps_init();
    rpm_init();

    // Display và LVGL sau cùng
    dashboard_init();
}

void loop() {
    // Cấp tick thời gian cho LVGL (bắt buộc để animate)
    static uint32_t last_tick = 0;
    uint32_t now = millis();
    lv_tick_inc(now - last_tick);
    last_tick = now;

    // LVGL render
    lv_timer_handler();

    // Cập nhật GPS
    gps_update();

    // Đọc dữ liệu và đẩy lên màn hình
    #if DEBUG_MOCK_DATA
        static unsigned long lastMock = 0;
        if (millis() - lastMock > 50) {
            lastMock = millis();
            updateMockData();
            dashboard_set_speed((int)mockSpeed);
            dashboard_set_rpm(mockRpm);
            dashboard_set_gps(10.776889f, 106.700806f); // Mock: TP.HCM
        }
    #else
        dashboard_set_speed(gps_get_speed_kmh());
        dashboard_set_rpm(rpm_get());
        dashboard_set_gps(gps_get_lat(), gps_get_lng());
    #endif

    // Xử lý nút bấm xi nhan
    turn_signal_update();
    headlight_update();

    delay(5);
}
