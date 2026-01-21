#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// ========== WiFi Configuration ==========
const char *ssid = "FRITZ!Box 6591 Cable VG";  // Change to your WiFi SSID
const char *password = "99463263925230016110"; // Change to your WiFi password

// ========== MQTT Configuration ==========
const char *mqtt_server = "192.168.178.166"; // Change to your Raspberry Pi IP
const int mqtt_port = 1883;
const char *mqtt_user = "xudong";     // Leave empty "" if not configured
const char *mqtt_password = "112233"; // Leave empty "" if not configured

// MQTT Topics
const char *command_topic = "smartlight/lamp/command";
const char *state_topic = "smartlight/lamp/state";

WiFiClient espClient;
PubSubClient mqtt(espClient);

// ========== Simulated Lamp State ==========
struct LampState
{
    bool isOn = false;
    uint8_t red = 255;
    uint8_t green = 255;
    uint8_t blue = 255;
    uint8_t brightness = 100; // 0-100
} lamp;

// ========== Helper Functions ==========

// Print separator line
void printSeparator()
{
    Serial.println("================================================");
}

// Display current lamp state (simulated visualization)
void displayLampState()
{
    printSeparator();
    Serial.println("💡 Current Lamp State:");
    Serial.printf("   Status: %s\n", lamp.isOn ? "🟢 ON" : "🔴 OFF");
    Serial.printf("   Brightness: %d%%\n", lamp.brightness);
    Serial.printf("   Color: RGB(%d, %d, %d)\n", lamp.red, lamp.green, lamp.blue);

    // Calculate actual display color (considering brightness)
    if (lamp.isOn)
    {
        uint8_t displayR = (lamp.red * lamp.brightness) / 100;
        uint8_t displayG = (lamp.green * lamp.brightness) / 100;
        uint8_t displayB = (lamp.blue * lamp.brightness) / 100;
        Serial.printf("   Actual Output: RGB(%d, %d, %d)\n", displayR, displayG, displayB);

        // Simple color name recognition
        String colorName = "Unknown";
        if (displayR > 200 && displayG < 50 && displayB < 50)
            colorName = "Red";
        else if (displayR < 50 && displayG > 200 && displayB < 50)
            colorName = "Green";
        else if (displayR < 50 && displayG < 50 && displayB > 200)
            colorName = "Blue";
        else if (displayR > 200 && displayG > 200 && displayB < 50)
            colorName = "Yellow";
        else if (displayR > 200 && displayG < 50 && displayB > 200)
            colorName = "Purple";
        else if (displayR < 50 && displayG > 200 && displayB > 200)
            colorName = "Cyan";
        else if (displayR > 200 && displayG > 200 && displayB > 200)
            colorName = "White";
        else if (displayR < 30 && displayG < 30 && displayB < 30)
            colorName = "Off/Black";
        else
            colorName = "Mixed Color";

        Serial.printf("   🎨 Color Effect: %s\n", colorName.c_str());
    }
    else
    {
        Serial.println("   Actual Output: Lamp is OFF");
    }
    printSeparator();
}

// WiFi Connection
void setupWiFi()
{
    Serial.println("\n🌐 Starting WiFi connection...");
    Serial.printf("   SSID: %s\n", ssid);

    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\n✅ WiFi connected successfully!");
        Serial.printf("   IP Address: %s\n", WiFi.localIP().toString().c_str());
        Serial.printf("   Signal Strength: %d dBm\n", WiFi.RSSI());
    }
    else
    {
        Serial.println("\n❌ WiFi connection failed!");
    }
    printSeparator();
}

// Publish lamp state to MQTT
void publishState()
{
    StaticJsonDocument<256> doc;

    doc["state"] = lamp.isOn ? "ON" : "OFF";
    doc["brightness"] = lamp.brightness;
    doc["color"]["r"] = lamp.red;
    doc["color"]["g"] = lamp.green;
    doc["color"]["b"] = lamp.blue;

    char buffer[256];
    serializeJson(doc, buffer);

    bool success = mqtt.publish(state_topic, buffer, true);

    Serial.println("\n📤 Publishing state to MQTT:");
    Serial.printf("   Topic: %s\n", state_topic);
    Serial.printf("   Message: %s\n", buffer);
    Serial.printf("   Result: %s\n", success ? "✅ Success" : "❌ Failed");
}

// Apply lamp changes
void applyLampChange()
{
    Serial.println("\n🔄 Applying lamp changes...");
    displayLampState();
    publishState();
}

// MQTT message callback
void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    Serial.println("\n📨 Received MQTT Message:");
    Serial.printf("   Topic: %s\n", topic);

    // Convert payload to string
    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';
    Serial.printf("   Content: %s\n", message);

    // Parse JSON
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, message);

    if (error)
    {
        Serial.printf("   ❌ JSON parsing failed: %s\n", error.c_str());
        return;
    }

    Serial.println("   ✅ JSON parsed successfully");

    // Process commands
    bool stateChanged = false;

    if (doc.containsKey("state"))
    {
        String state = doc["state"].as<String>();
        bool newState = (state == "ON");
        if (newState != lamp.isOn)
        {
            lamp.isOn = newState;
            stateChanged = true;
            Serial.printf("   🔆 Status changed: %s\n", lamp.isOn ? "ON" : "OFF");
        }
    }

    if (doc.containsKey("brightness"))
    {
        uint8_t newBrightness = doc["brightness"];
        if (newBrightness != lamp.brightness)
        {
            lamp.brightness = newBrightness;
            stateChanged = true;
            Serial.printf("   ☀️  Brightness changed: %d%%\n", lamp.brightness);
        }
    }

    if (doc.containsKey("color"))
    {
        uint8_t newR = doc["color"]["r"];
        uint8_t newG = doc["color"]["g"];
        uint8_t newB = doc["color"]["b"];

        if (newR != lamp.red || newG != lamp.green || newB != lamp.blue)
        {
            lamp.red = newR;
            lamp.green = newG;
            lamp.blue = newB;
            stateChanged = true;
            Serial.printf("   🎨 Color changed: RGB(%d, %d, %d)\n", lamp.red, lamp.green, lamp.blue);
        }
    }

    // If state changed, apply and publish new state
    if (stateChanged)
    {
        applyLampChange();
    }
    else
    {
        Serial.println("   ℹ️  No changes detected");
    }
}

// Reconnect to MQTT
void reconnectMQTT()
{
    while (!mqtt.connected())
    {
        Serial.println("\n🔌 Connecting to MQTT Broker...");
        Serial.printf("   Server: %s:%d\n", mqtt_server, mqtt_port);

        String clientId = "ESP32Lamp-";
        clientId += String(random(0xffff), HEX);
        Serial.printf("   Client ID: %s\n", clientId.c_str());

        if (mqtt.connect(clientId.c_str(), mqtt_user, mqtt_password))
        {
            Serial.println("   ✅ MQTT connected successfully!");

            mqtt.subscribe(command_topic);
            Serial.printf("   📥 Subscribed to topic: %s\n", command_topic);

            // Publish initial state
            publishState();
            displayLampState();
        }
        else
        {
            Serial.printf("   ❌ Connection failed, error code: %d\n", mqtt.state());
            Serial.println("   ⏳ Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    printSeparator();
    Serial.println("🚀 Smart Lamp MQTT Test System Starting");
    Serial.println("   Version: 1.0 (Simulation Mode)");
    Serial.println("   Device: ESP32");
    printSeparator();

    // Connect to WiFi
    setupWiFi();

    // Configure MQTT
    mqtt.setServer(mqtt_server, mqtt_port);
    mqtt.setCallback(mqttCallback);
    mqtt.setBufferSize(512);

    Serial.println("\n✨ System initialization complete, waiting for MQTT connection...\n");
}

void loop()
{
    // Keep MQTT connected
    if (!mqtt.connected())
    {
        reconnectMQTT();
    }
    mqtt.loop();

    // Output current state every 30 seconds (optional)
    static unsigned long lastHeartbeat = 0;
    if (millis() - lastHeartbeat > 30000)
    {
        lastHeartbeat = millis();
        Serial.println("\n💓 Heartbeat - System running normally");
        displayLampState();
    }

    delay(10);
}
