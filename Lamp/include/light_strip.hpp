#ifndef LIGHT_STRIP_HPP
#define LIGHT_STRIP_HPP

#include <string>

#include <Adafruit_NeoPixel.h>

#include "setting.hpp"

class light_strip {
    uint32_t pixels;
    Adafruit_NeoPixel strip;
    bool strip_on = false;
    uint8_t r = 0, g = 0, b = 0, w = 0, brightness = 0;
    std::string mode = "color";
    uint16_t animation_state = 0;

public:
    using color = color_t;
    using setting = setting_t;

    light_strip(uint32_t pixels, uint8_t pin, uint8_t initial_brightness)
        : pixels(pixels), strip(pixels, pin, NEO_GRBW + NEO_KHZ800), brightness{initial_brightness} {}

    void init();

    void update();
    void update_party_mode();
    void reset_animation_state();

    // Setters
    void set_all(color color);
    void set_power(bool on);
    void setColor(color& color);
    void set_mode(std::string mode);
    void set_brightness(uint8_t& brightness);
    void set_animation_state(uint16_t animation_state);

    // Getters
    bool is_on();
    uint8_t red();
    uint8_t green();
    uint8_t blue();
    uint8_t white();
    uint8_t get_brightness();
    std::string get_mode();
    uint16_t get_animation_state();
};

#endif