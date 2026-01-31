//
// Created by Amsakan on 15.01.26.
//

#ifndef RADAR_AIR_SENSOR_H
#define RADAR_AIR_SENSOR_H

#include <sstream>
#include <string>

#include <SparkFun_SCD4x_Arduino_Library.h>

#include "../Config.hpp"
#include "data.hpp"

class air_sensor {
public:
    using data = data_t;

    void init();
    data measure();
private:
    SCD4x air_sensor_;
    data last_measurement = {0, 0,0};
};

#endif // RADAR_AIR_SENSOR_H
