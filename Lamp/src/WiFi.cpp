#include <WiFi.h>

#include "Config.hpp"
#include "WiFi.hpp"

using namespace net;

void wifi::init() {
  Serial.println("\n[2/3] Connecting to WiFi...");
  Serial.printf("  - SSID: %s\n", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < WIFI_CONNECTION_ATTEMPTS)
  {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\n  ✓ WiFi Connected!");
    Serial.printf("  - IP Address: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("  - Signal Strength: %d dBm\n", WiFi.RSSI());
  }
  else
  {
    Serial.println("\n  ✗ WiFi Connection Failed!");
  }
}