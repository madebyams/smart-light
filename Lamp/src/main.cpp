#include <cstdint>
#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "LightStrip.hh"

// LED Strip Configuration
#define NUM_PIXELS 100
#define DATA_PIN 23
#define CLOCK_PIN 18
LightStrip strip(NUM_PIXELS, DATA_PIN, CLOCK_PIN);

const char *ssid = "FRITZ!Box 6591 Cable VG";  // set your WiFi SSID
const char *password = "99463263925230016110"; // set your WiFi Password
//  Der Router and der HTW
//  const char* ssid = "FRITZ!Box 6690 LR";
//  const char* password = "69662372082075794623";
const char *mqtt_server = "192.168.178.166"; // Home Assistant IP
const char *mqtt_user = "xudong";            // MQTT Username (Home Assistant login username)
const char *mqtt_password = "112233";        // MQTT Password (Home Assistant login password)
const char *mqtt_set_topic = "home/ledstrip/set";
const char *mqtt_status_topic = "home/ledstrip/status";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
bool stripOn = false;
uint8_t r = 0, g = 0, b = 0;

// Function Prototypes
void reconnect();
void mqttCallback(char *topic, byte *payload, unsigned int len);
void updateStrip();
void publishStatus();

void setup()
{
  Serial.begin(115200);
  delay(1000); // Wait for Serial to initialize

  Serial.println("\n\n========== ESP32 LED Strip Starting ==========");
  Serial.printf("Chip Model: %s\n", ESP.getChipModel());
  Serial.printf("CPU Freq: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());

  // LED Strip Initialization
  Serial.println("\n[1/3] Initializing LED Strip...");
  Serial.printf("  - Pixels: %d\n", NUM_PIXELS);
  Serial.printf("  - Data Pin: %d\n", DATA_PIN);
  Serial.printf("  - Clock Pin: %d\n", CLOCK_PIN);
  strip.init();
  Serial.println("  ✓ LED Strip initialized");

  // WiFi connection
  Serial.println("\n[2/3] Connecting to WiFi...");
  Serial.printf("  - SSID: %s\n", ssid);
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30)
  {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\n  ✓ WiFi Connected!");
    Serial.printf("  - IP Address: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("  - Signal Strength: %d dBm\n", WiFi.RSSI());
  }
  else
  {
    Serial.println("\n  ✗ WiFi Connection Failed!");
  }

  // MQTT Setup
  Serial.println("\n[3/3] Setting up MQTT...");
  Serial.printf("  - Server: %s:1883\n", mqtt_server);
  Serial.printf("  - User: %s\n", mqtt_user);
  Serial.printf("  - Subscribe Topic: %s\n", mqtt_set_topic);
  Serial.printf("  - Publish Topic: %s\n", mqtt_status_topic);
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(mqttCallback);

  Serial.println("\n========== Setup Complete ==========\n");
}

void loop()
{
  if (!mqttClient.connected())
  {
    Serial.println("[WARN] MQTT disconnected, reconnecting...");
    reconnect();
  }
  mqttClient.loop();
  updateStrip();
  delay(50);
}

void reconnect()
{
  int attempts = 0;
  while (!mqttClient.connected() && attempts < 5)
  {
    attempts++;
    Serial.printf("[MQTT] Connection attempt %d/5...\n", attempts);

    if (mqttClient.connect("ESP32_LightStrip", mqtt_user, mqtt_password))
    {
      Serial.println("[MQTT] ✓ Connected successfully!");
      Serial.printf("[MQTT] Subscribing to: %s\n", mqtt_set_topic);

      if (mqttClient.subscribe(mqtt_set_topic))
      {
        Serial.println("[MQTT] ✓ Subscribed successfully!");
      }
      else
      {
        Serial.println("[MQTT] ✗ Subscribe failed!");
      }

      publishStatus();
    }
    else
    {
      Serial.printf("[MQTT] ✗ Connection failed! Error code: %d\n", mqttClient.state());
      Serial.println("       Error codes: -4=timeout, -3=lost, -2=failed, -1=disconnected");
      Serial.println("       0=connected, 1=bad protocol, 2=rejected, 3=unavailable, 4=bad credentials, 5=unauthorized");
      delay(5000);
    }
  }

  if (!mqttClient.connected())
  {
    Serial.println("[MQTT] ✗ Failed to connect after 5 attempts, will retry in next loop");
  }
}

void mqttCallback(char *topic, byte *payload, unsigned int len)
{
  String msg;
  for (uint16_t i = 0; i < len; i++)
    msg += (char)payload[i];

  Serial.println("\n========== MQTT Message Received ==========");
  Serial.printf("Topic: %s\n", topic);
  Serial.printf("Payload: %s\n", msg.c_str());
  Serial.printf("Length: %d bytes\n", len);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, msg);

  if (error)
  {
    Serial.printf("[ERROR] JSON parsing failed: %s\n", error.c_str());
    Serial.println("==========================================\n");
    return;
  }

  bool prevState = stripOn;
  uint8_t prevR = r, prevG = g, prevB = b;

  stripOn = doc["state"] == "ON";
  if (stripOn)
  {
    r = doc["color"]["r"] | 0;
    g = doc["color"]["g"] | 0;
    b = doc["color"]["b"] | 0;
  }

  Serial.println("Parsed values:");
  Serial.printf("  - State: %s -> %s\n", prevState ? "ON" : "OFF", stripOn ? "ON" : "OFF");
  if (stripOn)
  {
    Serial.printf("  - Color: RGB(%d,%d,%d) -> RGB(%d,%d,%d)\n", prevR, prevG, prevB, r, g, b);
  }
  Serial.println("==========================================\n");

  publishStatus();
}

void updateStrip()
{
  static unsigned long lastLog = 0;
  static bool lastState = false;
  static uint8_t lastR = 0, lastG = 0, lastB = 0;

  if (stripOn)
  {
    strip.fillColor(r, g, b);
  }
  else
  {
    strip.fillColor(0, 0, 0);
  }

  // Log every 5 seconds or on state/color change
  if (millis() - lastLog > 5000 || lastState != stripOn || lastR != r || lastG != g || lastB != b)
  {
    Serial.printf("[LED] State: %s", stripOn ? "ON" : "OFF");
    if (stripOn)
    {
      Serial.printf(" | Color: RGB(%d,%d,%d)", r, g, b);
    }
    Serial.printf(" | Free Heap: %d\n", ESP.getFreeHeap());

    lastLog = millis();
    lastState = stripOn;
    lastR = r;
    lastG = g;
    lastB = b;
  }
}

void publishStatus()
{
  DynamicJsonDocument doc(512);
  doc["state"] = stripOn ? "ON" : "OFF";
  if (stripOn)
  {
    JsonObject color = doc.createNestedObject("color");
    color["r"] = r;
    color["g"] = g;
    color["b"] = b;
  }

  char buf[256];
  size_t len = serializeJson(doc, buf);

  Serial.println("\n---------- Publishing Status ----------");
  Serial.printf("Topic: %s\n", mqtt_status_topic);
  Serial.printf("Message: %s\n", buf);
  Serial.printf("Size: %d bytes\n", len);

  if (mqttClient.publish(mqtt_status_topic, buf))
  {
    Serial.println("✓ Published successfully!");
  }
  else
  {
    Serial.println("✗ Publish failed!");
  }
  Serial.println("---------------------------------------\n");
}