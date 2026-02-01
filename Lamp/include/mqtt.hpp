#ifndef MQTT_HPP
#define MQTT_HPP

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "light_strip.hpp"

namespace net::mqtt {
        extern WiFiClient wifi_client;
        extern PubSubClient client;

        void init(MQTT_CALLBACK_SIGNATURE);
        bool is_connected();
        void reconnect(light_strip& light_strip);
        void publish_status(light_strip& light_strip);
}


#endif