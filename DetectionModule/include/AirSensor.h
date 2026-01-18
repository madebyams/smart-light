//
// Created by Amsakan on 15.01.26.
//

#ifndef RADAR_AIRSENSOR_H
#define RADAR_AIRSENSOR_H
#include <SparkFun_SCD4x_Arduino_Library.h>

#define FAILURE_LED  33

namespace AirSensor {
    struct Data {
        uint16_t co2;
        float temperature;
        float humidity;
    };

    class Sensor {
        SCD4x myAirSensor;
    public:
        Sensor(): myAirSensor() {}
        void init();
        Data measure();
    };
}
#endif //RADAR_AIRSENSOR_H