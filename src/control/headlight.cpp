#include "headlight.h"
#include <Arduino.h>
#include "../config.h"
#include "../ui/dashboard.h"

static bool high_beam = false;

void headlight_init() {
    pinMode(PIN_RELAY_HEADLIGHT, OUTPUT);
    pinMode(PIN_BTN_HEADLIGHT,   INPUT_PULLUP);
    digitalWrite(PIN_RELAY_HEADLIGHT, HIGH); // Đèn cốt bật mặc định
}

void headlight_update() {
    if (digitalRead(PIN_BTN_HEADLIGHT) == LOW) {
        high_beam = !high_beam;
        delay(200); // Debounce
        digitalWrite(PIN_RELAY_HEADLIGHT, HIGH); // Luôn bật đèn
        dashboard_set_headlight(high_beam);
    }
}
