#pragma once

void  gps_init();
void  gps_update();
int   gps_get_speed_kmh();
float gps_get_lat();
float gps_get_lng();
bool  gps_has_fix();
