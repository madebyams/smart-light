#include <DFRobot_mmWave_Radar.h>

HardwareSerial mySerial(1);
DFRobot_mmWave_Radar sensor(&mySerial);

#define LED_BUILTIN 2

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200, SERIAL_8N1, 16, 17);  //RX,TX
  pinMode(LED_BUILTIN, OUTPUT);

  sensor.factoryReset();     //Restore to the factory settings
  sensor.DetRangeCfg(0, 9);  //The detection range is as far as 9m
  sensor.OutputLatency(0, 0);
}

void loop() {
  int val = sensor.readPresenceDetection();
  digitalWrite(LED_BUILTIN, val);
  Serial.println(val);
}