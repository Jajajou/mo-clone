#pragma once

// === PIN MAPPING — ESP32-S3 ===

// Màn hình GC9A01 (SPI)
#define PIN_TFT_MOSI  11
#define PIN_TFT_SCLK  12
#define PIN_TFT_CS    10
#define PIN_TFT_DC    9
#define PIN_TFT_RST   8
#define PIN_TFT_BL    46   // Backlight (PWM)

// GPS NEO-6M (UART2)
#define PIN_GPS_RX    16
#define PIN_GPS_TX    17

// Relay điều khiển (output)
#define PIN_RELAY_HEADLIGHT   4   // Đèn pha
#define PIN_RELAY_TURN_LEFT   5   // Xi nhan trái
#define PIN_RELAY_TURN_RIGHT  6   // Xi nhan phải
#define PIN_RELAY_HORN        7   // Còi

// Nút bấm (input qua optocoupler, active LOW)
#define PIN_BTN_TURN_LEFT    38
#define PIN_BTN_TURN_RIGHT   39
#define PIN_BTN_HEADLIGHT    40
#define PIN_BTN_HORN         41

// Cảm biến RPM (từ bô-bin, qua LM393)
#define PIN_RPM_SIGNAL       2

// === THÔNG SỐ XE SR400 ===
#define ENGINE_CYLINDERS     1      // SR400: 1 xi-lanh
#define MAX_RPM              9000   // Vòng tua tối đa
#define MAX_SPEED_KMH        150    // Tốc độ tối đa hiển thị

// === THÔNG SỐ XI NHAN ===
#define TURN_BLINK_MS        500    // Chu kỳ nháy xi nhan (ms)

// === CHẾ ĐỘ DEBUG (tắt khi gắn lên xe thật) ===
#define DEBUG_MOCK_DATA      true   // Dùng data giả để test UI
#define DEBUG_SERIAL         true
