//
// Created by Amsakan on 15.01.26.
//
#include "Mic.hpp"

#include <Arduino.h>

void mic::init() {
    pinMode(pin_, INPUT);
}

int mic::measure() {
    return analogRead(pin_);
}
