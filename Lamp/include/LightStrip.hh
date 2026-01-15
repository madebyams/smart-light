#ifndef LIGHT_STRIP_HH
#define LIGHT_STRIP_HH

#include <cstdint>
#include <Adafruit_WS2801.h>

class LightStrip {
    uint32_t pixels;
    Adafruit_WS2801 strip;
public:
    LightStrip(uint32_t pixels, uint8_t data_pin, uint8_t clock_pin)
        : pixels(pixels), strip(pixels, data_pin, clock_pin) {}

    void init();
    void fillColor(uint8_t r, uint8_t g, uint8_t b);
};

#endif