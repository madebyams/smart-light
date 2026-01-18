#include <Arduino.h>
#include "RGBSensor.h"

namespace RGBSensor {
    void RGBSensor::init() {
        if (!rgb_sensor.init()) {
            Serial.println("Failed to init RGB module!");
            while(true) {;;}
        }
    }

    Color RGBSensor::measure() {
        Color color = {
            .red = rgb_sensor.readRed(),
            .green = rgb_sensor.readGreen(),
            .blue = rgb_sensor.readBlue(),
        };

        return color;
    }

}