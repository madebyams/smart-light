#include "LightStrip.hh"

void LightStrip::init() {
    // Initialize LED strcleip
  strip.begin();
  strip.show(); // Clear all LEDs (turn off)
}

void LightStrip::fillColor(uint8_t r, uint8_t g, uint8_t b) {
  for (uint16_t i = 0; i < pixels; i++) {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}
