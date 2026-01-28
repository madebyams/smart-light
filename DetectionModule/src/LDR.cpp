//
// Created by Amsakan on 15.01.26.
//
#include "LDR.hpp"

#include <Arduino.h>

void LDR::init() {
    pinMode(pin, INPUT);
}

int LDR::measure() {
    return analogRead(pin);
}
