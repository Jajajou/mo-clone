#include "gps_reader.h"
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#include "../config.h"

static TinyGPSPlus gps;
static HardwareSerial gpsSerial(2); // UART2

void gps_init() {
    gpsSerial.begin(9600, SERIAL_8N1, PIN_GPS_RX, PIN_GPS_TX);
}

void gps_update() {
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }
}

int gps_get_speed_kmh() {
    if (!gps.speed.isValid()) return 0;
    return (int)gps.speed.kmph();
}

float gps_get_lat() {
    if (!gps.location.isValid()) return 0.0f;
    return (float)gps.location.lat();
}

float gps_get_lng() {
    if (!gps.location.isValid()) return 0.0f;
    return (float)gps.location.lng();
}

bool gps_has_fix() {
    return gps.location.isValid();
}
