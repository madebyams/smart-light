//
// Created by Amsakan on 15.01.26.
//

#ifndef RADAR_RADARSENSOR_H
#define RADAR_RADARSENSOR_H
#include <cstdint>

#include <DFRobot_mmWave_Radar.h>


class RadarSensor {
    uint8_t rx, tx;
    HardwareSerial hwSerial;
    DFRobot_mmWave_Radar sensor;
public:
    RadarSensor(const uint8_t rx, const uint8_t tx, uint8_t uart_nr)
        : rx(rx), tx(tx), hwSerial(uart_nr), sensor(&hwSerial) {}

    void init();
    bool measure();
};
#endif //RADAR_RADARSENSOR_H