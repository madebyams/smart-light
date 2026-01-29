//
// Created by Amsakan on 28.01.26.
//

#include <PubSubClient.h>
#include <WiFi.h>

#include "Mqtt.hpp"
#include "Config.hpp"

using namespace net;

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

void mqtt::init() {
    mqtt_client.setServer(MQTT_SERVER, MQTT_PORT);
}

void mqtt::write(std::string message) {
    mqtt_client.print(message.c_str());
}