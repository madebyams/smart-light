#include <cstdint>

#include <Arduino.h>
#include <SPI.h>
#include "LightStrip.hh"

// Change this value to match the actual number of LEDs in your strip
#define NUM_PIXELS  100
#define DATA_PIN    23
#define CLOCK_PIN   18

LightStrip strip(NUM_PIXELS, DATA_PIN, CLOCK_PIN);

void setup() {
    strip.init();
    strip.fillColor(255, 0, 0);
}

void loop() {}
