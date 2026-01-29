//
// Created by Amsakan on 15.01.26.
//

#ifndef RADAR_RADARSENSOR_H
#define RADAR_RADARSENSOR_H
#include <cstdint>

#include <DFRobot_mmWave_Radar.h>


class radar_sensor {
    uint8_t rx_;
    uint8_t tx_;
    HardwareSerial hw_serial_;
    DFRobot_mmWave_Radar sensor_;
public:
    radar_sensor(uint8_t rx, uint8_t tx, uint8_t uart_nr)
        : rx_(rx)
        , tx_(tx)
        , hw_serial_(uart_nr)
        , sensor_(&hw_serial_) {}

    void init();
    bool measure();
};

#endif //RADAR_RADARSENSOR_H