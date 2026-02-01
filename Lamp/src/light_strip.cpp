#include "light_strip.hpp"

void light_strip::init() {
  strip.begin();
  strip.setBrightness(this->brightness);
  strip.show();
}

void light_strip::update() {
  if (strip_on) {
    if (mode == "party") {
      update_party_mode();
    } else {
      set_all({r, g, b, w});
    }
  } else {
    set_all({0, 0, 0, 0});
  }
}

void light_strip::update_party_mode() {
  static unsigned long lastUpdate = 0;
  static const uint16_t UPDATE_INTERVAL =
      50;  // Update every 50ms for smooth animation

  if (millis() - lastUpdate < UPDATE_INTERVAL) {
    return;
  }
  lastUpdate = millis();

  // Rotate through rainbow around the ring
  for (uint16_t i = 0; i < pixels; i++) {
    // Calculate hue for this LED based on position and animation state
    uint16_t hue =
        (i * 360 / pixels + animation_state) % 360;  // Spread rainbow around ring
    uint8_t saturation = 255;
    uint8_t value = brightness;

    color color;
    color = color::hsvToRgb(hue, saturation, value);
    strip.setPixelColor(
        i, strip.Color(color.red, color.green, color.blue, 0));  // No white channel for rainbow
  }
  strip.show();

  // Increment animation state for next frame
  animation_state = (animation_state + 5) % 360;  // Rotate in 5° steps
}

void light_strip::reset_animation_state() {
  this->set_animation_state(0);
}

void light_strip::set_all(color color) {
  for (int i = 0; i < pixels; i++) {
    strip.setPixelColor(i, strip.Color(color.red, color.green, color.blue, color.white));
  }
  strip.show();
}


void light_strip::set_power(bool on) {
  this->strip_on = on;
}

void light_strip::setColor(color& color) {
  this->r = color.red;
  this->g = color.green;
  this->b = color.blue;
  this->w = color.white;
}

void light_strip::set_brightness(uint8_t& brightness) {
  this->brightness = brightness;
}

void light_strip::set_mode(std::string mode) {
  this->mode = mode;
}

void light_strip::set_animation_state(uint16_t animation_state) {
  this->animation_state = animation_state;
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
