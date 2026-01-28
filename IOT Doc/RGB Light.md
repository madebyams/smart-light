Devices
- BerryBase NMCU-ESP32 x 1
- Breadboard x 1
- 4 Pins RGB LED x 1
- Resistor x 3
- one side female one side male Cable x 4
- micro USB Cable x 1

Setting in Arduino IED
1. In *Board Manager* install the "esp32 by Esprissif"
2. Select *Tool --> Board --> esp32 --> ESP32 Dev Module*
3. Select *Tool --> Port "/dev/cu.usbserial-0001"*

<p align="left">
  <img src="RGB LED.png" alt="common anode RGB LED" width="300"><br>
  picture 1：common anode RGB LED
</p>


<p align="left">
  <img src="RGB LED Simulator.png" alt="" width="600"><br>
  picture 2： RGB LED Simulator
</p>

https://www.tinkercad.com/things/4UX9sdRDkRh-rgb-led


Example code in Arduino IDE (Mac OS)
```c++
int redPin= 2;

int greenPin = 4;

int bluePin = 5;

  

void setup() {

pinMode(redPin, OUTPUT);

pinMode(greenPin, OUTPUT);

pinMode(bluePin, OUTPUT);

}

  

void loop() {

setColor(255, 0, 0); // Red Color

delay(1000);

setColor(0, 255, 0); // Green Color

delay(1000);

setColor(0, 0, 255); // Blue Color

delay(1000);

setColor(255, 255, 0); // Yellow Color

delay(1000);

  

setColor(0, 255, 255); // Cyan Color

delay(1000);

setColor(255, 0, 255); // Magenta Color

delay(1000);

setColor(255, 165, 0); // Orange Color

delay(1000);

setColor(128, 0, 128); // Purple Color

delay(1000);

setColor(255, 255, 255); // White Color

delay(1000);

}

  

void setColor(int redValue, int greenValue, int blueValue) {

analogWrite(redPin, redValue);

analogWrite(greenPin, greenValue);

analogWrite(bluePin, blueValue);

}
```