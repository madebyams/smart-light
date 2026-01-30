#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPI.h>

#include "Config.hpp"
#include "LightStrip.hpp"
#include "Mqtt.hpp"
#include "WiFi.hpp"

// LED Strip Configuration
light_strip strip(LIGHT_LED_AMOUNT, LIGHT_PINS_DATA, LIGHT_PINS_CLOCK);

void mqtt_callback(char *topic, byte *payload, unsigned int len)
{
  String msg;
  for (uint16_t i = 0; i < len; i++)
    msg += (char)payload[i];

  Serial.println("\n========== MQTT Message Received ==========");
  Serial.printf("Topic: %s\n", topic);
  Serial.printf("Payload: %s\n", msg.c_str());
  Serial.printf("Length: %d bytes\n", len);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, msg);

  if (error)
  {
    Serial.printf("[ERROR] JSON parsing failed: %s\n", error.c_str());
    Serial.println("==========================================\n");
    return;
  }
  // handle state
  if (doc.containsKey("state"))
  {
    String state = doc["state"];
    strip.setState(state == "ON");
    Serial.printf("[MQTT] Set state: %s\n", state.c_str());
  }

  // handle color
  if (doc.containsKey("color"))
  {
    strip.setColor(doc["color"]["r"], doc["color"]["g"], doc["color"]["b"]);
    Serial.printf("[MQTT] Set color: RGB(%d,%d,%d)\n", strip.red(), strip.green(), strip.blue());
  }
  Serial.println("==========================================\n");
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
