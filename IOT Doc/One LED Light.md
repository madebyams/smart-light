Devices
- BerryBase NMCU-ESP32 x 1
- Breadboard x 1
- 2 Pins LED x 1
- Resistor x 1
- one side female one side male Cable x 2
- micro USB Cable x 1

Setting in Arduino IED
1. In *Board Manager* install the "esp32 by Esprissif"
2. Select *Tool --> Board --> esp32 --> ESP32 Dev Module*
3. Select *Tool --> Port "/dev/cu.usbserial-0001"*

Tinkercard Similator
https://www.tinkercad.com/things/5exua8dE0Fx-led
![[LED Simulator.png]]

Example Code in Arduino IDE (Mac OS)
```c++
// This function runs once when the board is powered on or reset
void setup(){
   // Set digital pin 12 as an output pin
   pinMode(12, OUTPUT);
}

// This function runs repeatedly in a loop
void loop(){
   // Set pin 12 HIGH to turn the LED on
   digitalWrite(12, HIGH);  
   // Wait for 1 second (1000 milliseconds)
   delay(1000);
   // Set pin 12 LOW to turn the LED off
   digitalWrite(12, LOW);
   // Wait for 1 second (1000 milliseconds)
   delay(1000);           
}

```



