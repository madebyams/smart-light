//
// Created by Amsakan on 15.01.26.
//
#include "radar_sensor.hpp"

void radar_sensor::init() {
    hw_serial_.begin(115200, SERIAL_8N1, 16, 17);  // RX, TX
    sensor_.factoryReset();                         // Restore factory settings
    sensor_.DetRangeCfg(0, 9);                     // Detection range up to 9m
    sensor_.OutputLatency(0, 0);
}

bool radar_sensor::measure() {
    return sensor_.readPresenceDetection();
}
