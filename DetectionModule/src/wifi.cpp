//
// Created by Amsakan on 28.01.26.
//
#include "config.hpp"
#include <WiFi.h>
#include "wifi.hpp"

using namespace net;

void wifi::init() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    for (int attempts = 0; WiFi.status() != WL_CONNECTED && attempts < 30; attempts++) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi Connected!");
    }
}
