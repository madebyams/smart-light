//
// Created by Amsakan on 15.01.26.
//
#include "AirSensor.h"

#include <Wire.h>


namespace AirSensor {
    void Sensor::init() {
        pinMode(FAILURE_LED, OUTPUT);

        Wire.begin();
        if (myAirSensor.begin() == false) {
            digitalWrite(FAILURE_LED, HIGH);
        }
    }

    Data Sensor::measure() {
        Data data = {
            .co2 = myAirSensor.getCO2(),
            .temperature = myAirSensor.getTemperature(),
            .humidity = myAirSensor.getHumidity()
        };

        return data;
    }
}
