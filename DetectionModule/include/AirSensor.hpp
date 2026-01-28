//
// Created by Amsakan on 15.01.26.
//

#ifndef RADAR_AIRSENSOR_H
#define RADAR_AIRSENSOR_H
#include <sstream>

#include <SparkFun_SCD4x_Arduino_Library.h>

#include "Config.hpp"

#define FAILURE_LED  33

class AirSensor {
    SCD4x my_air_sensor;
public:
    struct Data {
        uint16_t co2;
        float temperature;
        float humidity;

        std::string to_string();
    };

    struct DataBuffer {
        uint16_t co2[BUFFER_SIZE];
        float temperature[BUFFER_SIZE];
        float humidity[BUFFER_SIZE];
    };

    void init();
    void measure(DataBuffer* data, int position);
};

#endif //RADAR_AIRSENSOR_H