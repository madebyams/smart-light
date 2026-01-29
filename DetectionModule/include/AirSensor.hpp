//
// Created by Amsakan on 15.01.26.
//

#ifndef RADAR_AIR_SENSOR_H
#define RADAR_AIR_SENSOR_H

#include <sstream>
#include <string>

#include <SparkFun_SCD4x_Arduino_Library.h>

#include "config.hpp"

#define FAILURE_LED 33

class air_sensor {
    SCD4x air_sensor_;
public:
    struct data {
        uint16_t co2;
        float temperature;
        float humidity;

        std::string to_string();
    };

    struct data_buffer {
        uint16_t co2[BUFFER_SIZE];
        float temperature[BUFFER_SIZE];
        float humidity[BUFFER_SIZE];
    };

    void init();
    void measure(data_buffer* data, int position);
};

#endif // RADAR_AIR_SENSOR_H
