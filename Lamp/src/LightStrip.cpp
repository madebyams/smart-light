#include "Config.hpp"
#include "LightStrip.hpp"

void light_strip::init() {
  Serial.println("\n[1/3] Initializing LED Strip...");
  Serial.printf("  - Pixels: %d\n", LIGHT_LED_AMOUNT);
  Serial.printf("  - Data Pin: %d\n", LIGHT_PINS_DATA);
  Serial.printf("  - Clock Pin: %d\n", LIGHT_PINS_CLOCK);

  strip.begin();
  strip.show(); // Clear all LEDs (turn off)

  Serial.println("  ✓ LED Strip initialized");
}

void light_strip::fill_color(uint8_t r, uint8_t g, uint8_t b) {
  for (uint16_t i = 0; i < pixels; i++) {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}

void light_strip::update() {
  static unsigned long last_log = 0;
  static bool last_state = false;
  static uint8_t last_r = 0, last_g = 0, last_b = 0;

  if (strip_on) {
    this->fill_color(r, g, b);
  } else {
    this->fill_color(0, 0, 0);
  }

  // Log every 5 seconds or on state/color change
  if (millis() - last_log > 5000 || last_state != strip_on || last_r != r || last_g != g || last_b != b) {
    Serial.printf("[LED] State: %s", strip_on ? "ON" : "OFF");
    if (strip_on) {
      Serial.printf(" | Color: RGB(%d,%d,%d)", r, g, b);
    }
    
    Serial.printf(" | Free Heap: %d\n", ESP.getFreeHeap());

    last_log = millis();
    last_state = strip_on;
    last_r = r;
    last_g = g;
    last_b = b;
  }
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