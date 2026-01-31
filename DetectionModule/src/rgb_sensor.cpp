#include <Arduino.h>
#include "rgb_sensor/rgb_sensor.hpp"


void rgb_sensor::init() {
    if (!rgb_sensor_.init()) {
        Serial.println("Failed to init RGB module!");
        while (true) { ;; }
    }
}

rgb_sensor::color rgb_sensor::measure() {
    color current_measurement = {
        .red = rgb_sensor_.readRed(),
        .green = rgb_sensor_.readGreen(),
        .blue = rgb_sensor_.readBlue(),
    };

    if (current_measurement != last_measurement_) {
        last_measurement_ = current_measurement;
    }

    return last_measurement_;
}

