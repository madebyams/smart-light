//
// Created by Amsakan on 15.01.26.
//
#include "RadarSensor.h"

void RadarSensor::init() {
    hwSerial.begin(115200, SERIAL_8N1, 16, 17);  //RX,TX
    sensor.factoryReset();     //Restore to the factory settings
    sensor.DetRangeCfg(0, 9);  //The detection range is as far as 9m
    sensor.OutputLatency(0, 0);
}

bool RadarSensor::measure() {
    return sensor.readPresenceDetection();
}
