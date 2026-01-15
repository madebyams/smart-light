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
    // Initialize serial port for debugging (optional)
    Serial.begin(115200);
    Serial.println("WS2801 test starting...");

    strip.init();
    // Turn the entire strip red
    strip.fillColor(255, 0, 0);
}

void loop() {}
