#include "../lib/DFRobot_mmWave_Radar/DFRobot_mmWave_Radar.hh"
#include <HardwareSerial.h>

HardwareSerial mySerial(1);
DFRobot_mmWave_Radar sensor(&mySerial);


void setup() {
    Serial.begin(115200);
    mySerial.begin(115200, SERIAL_8N1, 3, 1);  //RX,TX
    pinMode(2, OUTPUT);

    sensor.factoryReset();     //Restore to the factory settings
    sensor.DetRangeCfg(0, 9);  //The detection range is as far as 9m
    sensor.OutputLatency(0, 0);
}

void loop() {
    int val = sensor.readPresenceDetection();
    digitalWrite(2, val);
    Serial.println(val);
}