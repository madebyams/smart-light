#include <Arduino.h>
#include <DFR_Radar.h>

HardwareSerial radarSerial(2);
DFR_Radar radar_sensor(&radarSerial);

void setup() {

    Serial.begin(115200);
    radarSerial.begin(115200, SERIAL_8N1, 16, 17);

    pinMode(2, OUTPUT);
    radar_sensor.factoryReset();
    radar_sensor.setDetectionRange(0, 1);
    radar_sensor.setOutputLatency(0,0);
}

void loop() {
    if (radar_sensor.checkPresence()) {
        digitalWrite(2, HIGH);
    } else {
        digitalWrite(2, LOW);
    }

    delay(500);
}