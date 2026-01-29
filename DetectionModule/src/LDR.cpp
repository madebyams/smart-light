//
// Created by Amsakan on 15.01.26.
//
#include "LDR.hpp"

#include <Arduino.h>

void ldr::init() {
    pinMode(pin_, INPUT);
}

int ldr::measure() {
    return analogRead(pin_);
}
