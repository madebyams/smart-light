//
// Created by Amsakan on 15.01.26.
//
#include "ldr.hpp"
#include <Arduino.h>

void ldr::init() {
    pinMode(pin_, INPUT);
}

int ldr::measure() {
    int current_measurement = analogRead(pin_);

    if (current_measurement != last_measurement && current_measurement > 0) {
        last_measurement = current_measurement;
    }

    return last_measurement;
}
