//
// Created by Amsakan on 28.01.26.
//


#include <WiFi.h>

#include "mqtt.hpp"
#include "Config.hpp"

using namespace net;

mqtt::mqtt(PubSubClient* mqtt_client)
    : mqtt_client_(mqtt_client) {}



void mqtt::init() {
    mqtt_client_->setServer(MQTT_SERVER, MQTT_PORT);
    mqtt_client_->connect(MQTT_DEVICE_ID, MQTT_USER, MQTT_PASSWORD);
    mqtt_client_->subscribe(MQTT_TOPICS_MEASUREMENT_DATA);
}

void mqtt::reconnect() {
    int attempts = 0;
    while (!mqtt_client_->connected() && attempts < MQTT_CONNECTION_ATTEMPTS) {
        attempts++;
        Serial.printf("[MQTT] Connection attempt %d/5...\n", attempts);

        if (mqtt_client_->connect(MQTT_DEVICE_ID, MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("[MQTT] ✓ Connected successfully!");
            Serial.printf("[MQTT] Subscribing to: %s\n", MQTT_TOPICS_MEASUREMENT_DATA);

            if ( mqtt_client_->subscribe(MQTT_TOPICS_MEASUREMENT_DATA)) {
                Serial.println("[MQTT] ✓ Subscribed successfully!");
            }

            else {
                Serial.println("[MQTT] ✗ Subscribe failed!");
            }
        }

        else {
            Serial.printf("[MQTT] ✗ Connection failed! Error code: %d\n", mqtt_client_->state());
            delay(5000);
        }
    }

    if (!mqtt_client_->connected()) {
        Serial.println("[MQTT] ✗ Failed to connect after 5 attempts, will retry in next loop");
    }

}

bool mqtt::is_connected() {
    return mqtt_client_->connected();
}

void mqtt::write(std::string message) {
    mqtt_client_->publish(MQTT_TOPICS_MEASUREMENT_DATA, message.c_str());
}