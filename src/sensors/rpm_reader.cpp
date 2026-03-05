#include "rpm_reader.h"
#include <Arduino.h>
#include "../config.h"

// SR400: 1 xi-lanh, 4 kỳ → bô-bin đánh lửa 1 lần / 2 vòng trục khuỷu
// Mỗi xung interrupt = 1 lần đánh lửa = 2 vòng (720 độ)

static volatile unsigned long pulse_count = 0;
static unsigned long last_calc_time = 0;
static int current_rpm = 0;

static void IRAM_ATTR rpm_isr() {
    pulse_count++;
}

void rpm_init() {
    pinMode(PIN_RPM_SIGNAL, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_RPM_SIGNAL), rpm_isr, FALLING);
}

int rpm_get() {
    unsigned long now = millis();
    unsigned long elapsed = now - last_calc_time;

    // Tính lại mỗi 500ms
    if (elapsed >= 500) {
        unsigned long count = pulse_count;
        pulse_count = 0;
        last_calc_time = now;

        // pulses/500ms → pulses/min → RPM (nhân 2 vì 4 kỳ)
        current_rpm = (int)((count * 60000UL * 2) / elapsed);

        if (current_rpm > MAX_RPM) current_rpm = MAX_RPM;
    }

    return current_rpm;
}
