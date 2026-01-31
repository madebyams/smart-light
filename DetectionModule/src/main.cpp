#include <Arduino.h>
#include <WiFiClient.h>

#include "../include/air_sensor/air_sensor.hpp"
#include "config.hpp"
#include "ldr.hpp"
#include "masurement.hpp"
#include "mic.hpp"
#include "mqtt.hpp"
#include "PubSubClient.h"
#include "radar_sensor.hpp"
#include "rgb_sensor/rgb_sensor.hpp"
#include "wifi.hpp"

WiFiClient wifi_client;
PubSubClient pub_sub_client(wifi_client);
net::mqtt mqtt_client = net::mqtt(&pub_sub_client);

air_sensor air_sensor_instance;
ldr ldr_sensor(GPIO_LDR);
mic mic_sensor(GPIO_MIC);
radar_sensor radar_sensor(16, 17, 1);
rgb_sensor rgb_sensor(0x44);

measurement measurement;

void setup() {
  Serial.begin(115200);
  pinMode(GPIO_STATUS_LED, OUTPUT);

  net::wifi::init();
  mqtt_client.init();

  mic_sensor.init();
  ldr_sensor.init();
  radar_sensor.init();
  air_sensor_instance.init();
  rgb_sensor.init();
}

void loop() {
  if (!mqtt_client.is_connected()) {
    mqtt_client.reconnect();
  }


  measurement = {
    .brightness = ldr_sensor.measure(),
    .noise_level = mic_sensor.measure(),
    .presence = radar_sensor.measure(),
    .air_quality = air_sensor_instance.measure(),
    .light_color = rgb_sensor.measure()
  };

  mqtt_client.write(measurement.to_string().c_str());
  delay(5000);
}
