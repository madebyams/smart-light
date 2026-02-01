#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPI.h>

#include "config.hpp"
#include "light_strip.hpp"
#include "mqtt.hpp"
#include "setting.hpp"
#include "wifi.hpp"

// LED Strip Configuration
light_strip strip(LIGHT_LED_AMOUNT, LIGHT_PIN, LIGHT_BRIGHTNESS);

void mqtt_callback(char *topic, byte *payload, unsigned int len) {
  setting_t setting = setting_t::from_mqtt_payload(payload, len);

  setting.on_id = [](const std::string& id) {
    if (id.empty() || MQTT_DEVICE_ID == id) {
      return;
    }
  };

  setting.on_state = [](const std::string& state) {
    strip.set_power(state == "ON");
  };

  setting.on_mode = [](const std::string& mode) {
    strip.set_mode(mode);
    strip.reset_animation_state();
  };

  setting.on_color = [](color_t color) {
    strip.setColor(color);
  };

  setting.on_brightness = [](uint8_t brightness) {
    strip.set_brightness(brightness);
  };

  setting.apply();
  strip.update();
  net::mqtt::publish_status(strip);
}

void setup()
{
  Serial.begin(115200);
  delay(1000); // Wait for Serial to initialize

  Serial.println("\n\n========== ESP32 LED Strip Starting ==========");
  Serial.printf("Chip Model: %s\n", ESP.getChipModel());
  Serial.printf("CPU Freq: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());

  // LED Strip Initialization
  strip.init();

  net::wifi::init();

  // MQTT Setup
  net::mqtt::init(mqtt_callback);

  Serial.println("\n========== Setup Complete ==========\n");
}

void loop() {
  if (!net::mqtt::is_connected())
  {
    Serial.println("[WARN] MQTT disconnected, reconnecting...");
    net::mqtt::reconnect(strip);
  }

  net::mqtt::publish_status(strip);
  net::mqtt::client.loop();
  strip.update();
  delay(50);
}
