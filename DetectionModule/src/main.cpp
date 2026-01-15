#include <Arduino.h>
#include "AirSensor.h"
#include "LDR.h"
#include "Mic.h"
#include "RadarSensor.h"


#define LED_BUILTIN 2
#define LDR_PIN     15
#define MIC_PIN     26

AirSensor::Sensor airSensor;
LDR ldr(LDR_PIN);
Mic mic(MIC_PIN);
RadarSensor radar_sensor(16, 17, 1);


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  airSensor.init();
  ldr.init();
  mic.init();
  radar_sensor.init();
}

void loop() {
  bool radar_value = radar_sensor.measure();
  digitalWrite(LED_BUILTIN, radar_value);
  AirSensor::Data airSensorData = airSensor.measure();
  int micValue = mic.measure();
  int ldrValue = ldr.measure();

  Serial.print("Mic: ");
  Serial.println(micValue);

  Serial.print("Presence: ");
  Serial.println(radar_value);

  Serial.print("CO2: ");
  Serial.println(airSensorData.co2);

  Serial.print("Temperature: ");
  Serial.println(airSensorData.temperature);

  Serial.print("Humidity: ");
  Serial.println(airSensorData.humidity);

  Serial.print("LDR: ");
  Serial.println(ldrValue);

  Serial.println();

  delay(100);
}