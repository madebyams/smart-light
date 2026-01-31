#include "config.hpp"
#include "light_strip.hpp"

void light_strip::init() {
  strip.begin();
  strip.setBrightness(this->brightness);
  strip.show();
}

void light_strip::update() {
  if (strip_on) {
    if (mode == "party") {
      //updatePartyMode();
    } else {
      set_all(r, g, b, w);
    }
  } else {
    set_all(0, 0, 0, 0);
  }
}

void light_strip::reset_animation_state() {
  this->set_animation_state(0);
}

void light_strip::set_all(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
  for (int i = 0; i < pixels; i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue, white));
  }
  strip.show();
}


void light_strip::set_power(bool on) {
  this->strip_on = on;
}

void light_strip::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->w = w;
}

void light_strip::set_brightness(uint8_t brightness) {
  this->brightness = brightness;
}

void light_strip::set_mode(std::string mode) {
  this->mode = mode;
}

void light_strip::set_animation_state(uint16_t animation_state) {
  this->animation_state = 0;
}

bool light_strip::is_on() {
  return this->strip_on;
}

uint8_t light_strip::red() {
  return this->r;
}

uint8_t light_strip::green() {
  return this->g;
}

uint8_t light_strip::blue() {
  return this->b;
}

uint8_t light_strip::white() {
  return this->w;
}

uint8_t light_strip::get_brightness() {
  return this->brightness;
}

std::string light_strip::get_mode() {
  return this->mode;
}

uint16_t light_strip::get_animation_state() {
  return this->animation_state;
}
