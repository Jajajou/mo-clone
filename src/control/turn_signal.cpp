#include "turn_signal.h"
#include <Arduino.h>
#include "../config.h"
#include "../ui/dashboard.h"

static bool left_on   = false;
static bool right_on  = false;
static bool blink_state = false;
static unsigned long last_blink   = 0;
static unsigned long last_btn_left  = 0; // Debounce không blocking
static unsigned long last_btn_right = 0;
static bool prev_left  = HIGH;
static bool prev_right = HIGH;

void turn_signal_init() {
    pinMode(PIN_RELAY_TURN_LEFT,  OUTPUT);
    pinMode(PIN_RELAY_TURN_RIGHT, OUTPUT);
    pinMode(PIN_BTN_TURN_LEFT,    INPUT_PULLUP);
    pinMode(PIN_BTN_TURN_RIGHT,   INPUT_PULLUP);

    digitalWrite(PIN_RELAY_TURN_LEFT,  LOW);
    digitalWrite(PIN_RELAY_TURN_RIGHT, LOW);
}

void turn_signal_update() {
    unsigned long now = millis();

    // Debounce không blocking — chỉ kích hoạt khi nhả ra (falling edge + 50ms trôi qua)
    bool cur_left  = digitalRead(PIN_BTN_TURN_LEFT);
    bool cur_right = digitalRead(PIN_BTN_TURN_RIGHT);

    if (prev_left == HIGH && cur_left == LOW && now - last_btn_left > 50) {
        last_btn_left = now;
        right_on = false;
        left_on  = !left_on;
    }
    if (prev_right == HIGH && cur_right == LOW && now - last_btn_right > 50) {
        last_btn_right = now;
        left_on  = false;
        right_on = !right_on;
    }
    prev_left  = cur_left;
    prev_right = cur_right;

    // Xử lý nhấp nháy theo chu kỳ TURN_BLINK_MS
    if (millis() - last_blink >= TURN_BLINK_MS) {
        last_blink  = millis();
        blink_state = !blink_state;
    }

    bool show_left  = left_on  && blink_state;
    bool show_right = right_on && blink_state;

    digitalWrite(PIN_RELAY_TURN_LEFT,  show_left  ? HIGH : LOW);
    digitalWrite(PIN_RELAY_TURN_RIGHT, show_right ? HIGH : LOW);

    dashboard_set_turn_left(show_left);
    dashboard_set_turn_right(show_right);
}
