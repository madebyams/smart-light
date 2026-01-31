#include <Arduino.h>
#include <WiFiClient.h>

#include "Average.hpp"
#include "AirSensor.hpp"
#include "Config.hpp"
#include "LDR.hpp"
#include "Measurement.hpp"
#include "Mic.hpp"
#include "Mqtt.hpp"
#include "PubSubClient.h"
#include "RadarSensor.hpp"
#include "RGBSensor.hpp"
#include "WiFi.hpp"

WiFiClient wifi_client;
PubSubClient pub_sub_client(wifi_client);
net::mqtt mqtt_client = net::mqtt(&pub_sub_client);

air_sensor air_sensor_instance;
air_sensor::data_buffer air_data_buffer;

ldr ldr_sensor(GPIO_LDR);
int ldr_data_buffer[BUFFER_SIZE];

mic mic_sensor(GPIO_MIC);
int mic_data_buffer[BUFFER_SIZE];

radar_sensor radar_sensor_instance(16, 17, 1);
bool radar_sensor_buffer[BUFFER_SIZE];

rgb_sensor rgb_sensor_instance(0x44);
rgb_sensor::color_buffer rgb_sensor_buffer;

measurement measurement;

void setup() {
  Serial.begin(115200);
  pinMode(GPIO_STATUS_LED, OUTPUT);


  net::wifi::init();
  mqtt_client.init();


  mic_sensor.init();
  ldr_sensor.init();

  radar_sensor_instance.init();

  air_sensor_instance.init();

  rgb_sensor_instance.init();
  Serial.println();
}

void loop() {
  if (!mqtt_client.is_connected()) {
    mqtt_client.reconnect();
  }

  for (int i = 0; i < BUFFER_SIZE; i++) {
    air_sensor_instance.measure(&air_data_buffer, i);
    ldr_data_buffer[i] = ldr_sensor.measure();
    mic_data_buffer[i] = mic_sensor.measure();
    radar_sensor_buffer[i] = radar_sensor_instance.measure();
    rgb_sensor_instance.measure(&rgb_sensor_buffer, i);
  }

  measurement = {
    .brightness = average::calculate_average(ldr_data_buffer, BUFFER_SIZE),
    .noise_level = average::calculate_average(mic_data_buffer, BUFFER_SIZE),
    .presence = average::calculate_average(radar_sensor_buffer, BUFFER_SIZE),
    .air_quality = average::calculate_average(&air_data_buffer, BUFFER_SIZE),
    .light_color = average::calculate_average(&rgb_sensor_buffer, BUFFER_SIZE)
  };

  mqtt_client.write(measurement.to_string().c_str());
  delay(1000);
}
