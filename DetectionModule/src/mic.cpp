//
// Created by Amsakan on 15.01.26.
//
#include "mic.hpp"

#include <Arduino.h>

void mic::init() {
    pinMode(pin_, INPUT);
}

int mic::measure() {
    int current_measurement = analogRead(pin_);

    if (current_measurement != last_measurement) {
        last_measurement = current_measurement;
    }

    return last_measurement;
}
