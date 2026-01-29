#ifndef LIGHT_STRIP_HPP
#define LIGHT_STRIP_HPP

#include <cstdint>
#include <Adafruit_WS2801.h>

class light_strip {
    uint32_t pixels;
    Adafruit_WS2801 strip;
    bool strip_on = false;
    uint8_t r = 0, g = 0, b = 0;
public:
    light_strip(uint32_t pixels, uint8_t data_pin, uint8_t clock_pin)
        : pixels(pixels), strip(pixels, data_pin, clock_pin) {}

    void init();
    void fill_color(uint8_t r, uint8_t g, uint8_t b);
    void update();
    bool is_on();
    uint8_t red();
    uint8_t green();
    uint8_t blue();
};

#endif