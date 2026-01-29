#include "Config.hpp"
#include "Mqtt.hpp"

#include <ArduinoJson.h>

namespace net {
  namespace mqtt {
    WiFiClient wifi_client;
    PubSubClient client(wifi_client);
  }
}

using namespace net;

void mqtt::init(MQTT_CALLBACK_SIGNATURE) {
    Serial.println("\n[3/3] Setting up MQTT...");
    Serial.printf("  - Server: %s:1883\n", MQTT_SERVER);
    Serial.printf("  - User: %s\n", MQTT_USER);
    Serial.printf("  - Subscribe Topic: %s\n", MQTT_TOPICS_SET);
    Serial.printf("  - Publish Topic: %s\n", MQTT_TOPICS_STATUS);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback);
}

bool mqtt::is_connected() {
    return client.connected();
}

void mqtt::reconnect(light_strip& light_strip) {
  int attempts = 0;
  while (!is_connected() && attempts < MQTT_CONNECTION_ATTEMPTS) {
    attempts++;
    Serial.printf("[MQTT] Connection attempt %d/5...\n", attempts);

    if (client.connect(MQTT_DEVICE_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("[MQTT] ✓ Connected successfully!");
      Serial.printf("[MQTT] Subscribing to: %s\n", MQTT_TOPICS_SET);

      if (client.subscribe(MQTT_TOPICS_SET)) {
        Serial.println("[MQTT] ✓ Subscribed successfully!");
      }

      else {
        Serial.println("[MQTT] ✗ Subscribe failed!");
      }

      publish_status(light_strip);
    }
    else
    {
      Serial.printf("[MQTT] ✗ Connection failed! Error code: %d\n", client.state());
      Serial.println("       Error codes: -4=timeout, -3=lost, -2=failed, -1=disconnected");
      Serial.println("       0=connected, 1=bad protocol, 2=rejected, 3=unavailable, 4=bad credentials, 5=unauthorized");
      delay(5000);
    }
  }

  if (!client.connected()) {
    Serial.println("[MQTT] ✗ Failed to connect after 5 attempts, will retry in next loop");
  }
}

void mqtt::publish_status(light_strip& light_strip) {
  DynamicJsonDocument doc(512);
  doc["state"] = light_strip.is_on() ? "ON" : "OFF";
  if (light_strip.is_on()) {
    JsonObject color = doc.createNestedObject("color");
    color["r"] = light_strip.red();
    color["g"] = light_strip.green();
    color["b"] = light_strip.blue();
  }

  char buf[256];
  size_t len = serializeJson(doc, buf);

  Serial.println("\n---------- Publishing Status ----------");
  Serial.printf("Topic: %s\n", MQTT_TOPICS_STATUS);
  Serial.printf("Message: %s\n", buf);
  Serial.printf("Size: %d bytes\n", len);

  if (client.publish(MQTT_TOPICS_STATUS, buf)) {
    Serial.println("✓ Published successfully!");
  } else {
    Serial.println("✗ Publish failed!");
  }

  Serial.println("---------------------------------------\n");
}