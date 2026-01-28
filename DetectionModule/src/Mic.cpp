//
// Created by Amsakan on 15.01.26.
//
#include "Mic.hpp"

#include <Arduino.h>

void Mic::init() {
    pinMode(pin, INPUT);
}

int Mic::measure() {
    return analogRead(pin);
}
