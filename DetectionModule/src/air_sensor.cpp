//
// Created by Amsakan on 15.01.26.
//
#include "air_sensor/air_sensor.hpp"

#include <Wire.h>

void air_sensor::init() {
    Wire.begin();
    if (air_sensor_.begin() == false) {
        return;
    }
}

air_sensor::data air_sensor::measure() {
    data current_measurement = {
        .co2 = air_sensor_.getCO2(),
        .temperature = air_sensor_.getTemperature(),
        .humidity = air_sensor_.getHumidity()
    };

    if (current_measurement != last_measurement) {
        last_measurement = current_measurement;
    }

    return last_measurement;
}
