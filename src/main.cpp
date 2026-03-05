#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include "config.h"

// Hardware SPI qua Arduino SPI library (khác LovyanGFX dùng IDF-level)
static Adafruit_ILI9341 tft(&SPI, PIN_TFT_DC, PIN_TFT_CS, PIN_TFT_RST);

void setup() {
    // Turn signals
    pinMode(PIN_RELAY_TURN_LEFT,  OUTPUT);
    pinMode(PIN_RELAY_TURN_RIGHT, OUTPUT);
    pinMode(PIN_BTN_TURN_LEFT,    INPUT_PULLUP);
    pinMode(PIN_BTN_TURN_RIGHT,   INPUT_PULLUP);
    digitalWrite(PIN_RELAY_TURN_LEFT,  LOW);
    digitalWrite(PIN_RELAY_TURN_RIGHT, LOW);

    // Headlight
    pinMode(PIN_RELAY_HEADLIGHT, OUTPUT);
    pinMode(PIN_BTN_HEADLIGHT,   INPUT_PULLUP);
    digitalWrite(PIN_RELAY_HEADLIGHT, LOW);

    // Backlight
    pinMode(PIN_TFT_BL, OUTPUT);
    digitalWrite(PIN_TFT_BL, HIGH);

    // Display — hardware SPI, MOSI=11 SCK=12 là default FSPI của ESP32-S3
    SPI.begin(PIN_TFT_SCLK, -1, PIN_TFT_MOSI, PIN_TFT_CS);
    tft.begin();
    tft.setRotation(0);
    tft.fillScreen(ILI9341_BLUE);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.setCursor(60, 100);
    tft.println("MO.UNIT");
    tft.setTextSize(2);
    tft.setCursor(50, 150);
    tft.println("WORKING!");
}

static bool left_on  = false;
static bool right_on = false;
static bool blink_state = false;
static bool high_beam   = false;

static unsigned long last_blink = 0;
static bool prev_left  = HIGH;
static bool prev_right = HIGH;
static bool prev_beam  = HIGH;

void loop() {
    unsigned long now = millis();

    // Đọc nút
    bool cur_left  = digitalRead(PIN_BTN_TURN_LEFT);
    bool cur_right = digitalRead(PIN_BTN_TURN_RIGHT);
    bool cur_beam  = digitalRead(PIN_BTN_HEADLIGHT);

    // Xi nhan trái — toggle khi nhấn
    if (prev_left == HIGH && cur_left == LOW) {
        right_on = false;
        left_on  = !left_on;
        delay(50); // debounce đơn giản
    }
    // Xi nhan phải
    if (prev_right == HIGH && cur_right == LOW) {
        left_on  = false;
        right_on = !right_on;
        delay(50);
    }
    // Đèn pha
    if (prev_beam == HIGH && cur_beam == LOW) {
        high_beam = !high_beam;
        digitalWrite(PIN_RELAY_HEADLIGHT, high_beam ? HIGH : LOW);
        delay(50);
    }

    prev_left  = cur_left;
    prev_right = cur_right;
    prev_beam  = cur_beam;

    // Nhấp nháy xi nhan mỗi 500ms
    if (now - last_blink >= 500) {
        last_blink  = now;
        blink_state = !blink_state;
    }

    digitalWrite(PIN_RELAY_TURN_LEFT,  (left_on  && blink_state) ? HIGH : LOW);
    digitalWrite(PIN_RELAY_TURN_RIGHT, (right_on && blink_state) ? HIGH : LOW);
}
