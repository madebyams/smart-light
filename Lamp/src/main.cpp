#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPI.h>

#include "config.hpp"
#include "light_strip.hpp"
#include "mqtt.hpp"
#include "wifi.hpp"

// LED Strip Configuration
light_strip strip(LIGHT_LED_AMOUNT, LIGHT_PIN, LIGHT_BRIGHTNESS);

void mqtt_callback(char *topic, byte *payload, unsigned int len) {
  String msg;
  DynamicJsonDocument doc(1024);

  for (uint16_t i = 0; i < len; i++) {
    msg += static_cast<char>(payload[i]);
  }

  if (DeserializationError error = deserializeJson(doc, msg); error) {
    return;
  }

  const char* targetId = doc["id"] | "";
  if (strlen(targetId) == 0 || strcmp(MQTT_DEVICE_ID,targetId) != 0) {
    Serial.println("Wrong id!");
    return;
  }

  // handle state
  if (doc.containsKey("state")) {
    String state = doc["state"];
    strip.set_power(state == "ON");
  }

  if (const char* modeStr = doc["mode"] | ""; strlen(modeStr) > 0) {
    strip.set_mode(modeStr);
    strip.reset_animation_state();
  }


  // handle color
  if (doc.containsKey("color")) {
    strip.setColor(doc["color"]["r"], doc["color"]["g"], doc["color"]["b"], doc["color"]["w"]);
  }


  if (uint8_t newBrightness = doc["brightness"] | strip.get_brightness(); newBrightness != strip.get_brightness()) {
    strip.set_brightness(newBrightness);
  }

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

void loop()
{
  if (!net::mqtt::is_connected())
  {
    Serial.println("[WARN] MQTT disconnected, reconnecting...");
    net::mqtt::reconnect(strip);
  }

  net::mqtt::client.loop();
  strip.update();
  delay(50);
}
