#include <Arduino.h>
#include "Average.h"
#include "AirSensor.h"
#include "Config.h"
#include "LDR.h"
#include "Mic.h"
#include "RadarSensor.h"
#include "RGBSensor.h"


AirSensor air_sensor;
AirSensor::DataBuffer air_data_buffer;

LDR ldr(GPIO_LDR);
int ldr_data_buffer[BUFFER_SIZE];

Mic mic(GPIO_MIC);
int mic_data_buffer[BUFFER_SIZE];

RadarSensor radar_sensor(16, 17, 1);
bool radar_sensor_buffer[BUFFER_SIZE];

RGBSensor rgb_sensor(0x44);
RGBSensor::ColorBuffer rgb_sensor_buffer;


void setup() {
  Serial.begin(115200);
  pinMode(GPIO_STATUS_LED, OUTPUT);

  mic.init();
  ldr.init();

  radar_sensor.init();

  air_sensor.init();

  Serial.print("Initalizing‚ RGB Sensor");
  rgb_sensor.init();
  Serial.println();
}

void loop() {
  for(int i = 0; i < BUFFER_SIZE; i++) {
    air_sensor.measure(&air_data_buffer, i);
    ldr_data_buffer[i] = ldr.measure();
    mic_data_buffer[i] = mic.measure();
    radar_sensor_buffer[i] = radar_sensor.measure();
    rgb_sensor.measure(&rgb_sensor_buffer, i);
  }

  Serial.print("LDR Avg: ");
  Serial.println(Average::calulcate_average(ldr_data_buffer, BUFFER_SIZE));

  Serial.print("Mic Avg: ");
  Serial.println(Average::calulcate_average(mic_data_buffer, BUFFER_SIZE));

  AirSensor::Data air_avg = Average::calculate_average(&air_data_buffer, BUFFER_SIZE);
  Serial.print("Air avg: ");
  Serial.println(air_avg.to_string().c_str());

  RGBSensor::Color color_avg = Average::calculate_average(&rgb_sensor_buffer, BUFFER_SIZE);
  Serial.print("RGB avg: ");
  Serial.println(color_avg.to_string().c_str());

  delay(5000);
}