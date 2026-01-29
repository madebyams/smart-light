Devices
- BerryBase NMCU-ESP32 x 1
- ws2801-5050fc32-cv LED Strip and its charger
- one side female one side male Cable x 3
- micro USB Cable x 1

Setting in Arduino IED

1. In *Board Manager* install the "esp32 by Esprissif"
2. In Library Manager install the "Adafruit WS2801 Library by Adafruit"
3. Select *Tool --> Board --> esp32 --> ESP32 Dev Module*
4. Select *Tool --> Port "/dev/cu.usbserial-0001"* 

Note
	 The GND pin and 5V power pin of LED strip is already connected to the charger, therefor no need to connect them to the ESP32 anymore. 


Example Code in Arduino IDE (Mac OS)

```c++
#include <Adafruit_WS2801.h>
#include <SPI.h>

// Change this value to match the actual number of LEDs in your strip
const uint16_t NUM_PIXELS = 100;

// Change these to the actual GPIO pins you used
const int DATA_PIN  = 23;   // WS2801 Data pin
const int CLOCK_PIN = 18;   // WS2801 Clock pin

// Constructor using arbitrary pins (works for ESP32)
Adafruit_WS2801 strip = Adafruit_WS2801(NUM_PIXELS, DATA_PIN, CLOCK_PIN);

void setup() {
  // Initialize serial port for debugging (optional)
  Serial.begin(115200);
  Serial.println("WS2801 test starting...");

  // Initialize LED strip
  strip.begin();
  strip.show(); // Clear all LEDs (turn off)
}

void loop() {
  // Turn the entire strip red
  fillColor(255, 0, 0);
  delay(1000);

  // Turn the entire strip green
  fillColor(0, 255, 0);
  delay(1000);

  // Turn the entire strip blue
  fillColor(0, 0, 255);
  delay(1000);

  // Simple “chasing light” effect
  chaseOneColor(0, 255, 0, 30); // Yellow chase, 30ms speed
}

// Fill the entire strip with a single color
void fillColor(uint8_t r, uint8_t g, uint8_t b) {
  for (uint16_t i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();
}

// Single-color chasing light: light up each pixel one by one
void chaseOneColor(uint8_t r, uint8_t g, uint8_t b, int waitMs) {
  // Turn all LEDs off first
  fillColor(0, 0, 0);

  for (uint16_t i = 0; i < NUM_PIXELS; i++) {
    // Light up the current pixel
    strip.setPixelColor(i, r, g, b);
    strip.show();
    delay(waitMs);
    // Then turn it off before moving to the next one
    strip.setPixelColor(i, 0, 0, 0);
  }
}

```