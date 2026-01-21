# Device

- Raspberry Pi with Home Assistant OS 16.3
- ESP32-32
- Monitor

# Steps

## Hardware setting


1. connect the Raspberry PI with monitor and internet cable with router.(connect to wifi ist optional)
2. then we can see the IP addr of Home Assistant `IPv4 addresses for end 0: 192.xxx.xxx.xxx`
3. use other another PC in the same network,  im browser access http://192.xxx.xxx.xxx:8123
4. set the home assistant username and password.
5. Home Assistant → Settings → Add-ons → Add-on Store → MQTT Broker（Mosquitto）

## VS Code setting 

1. `brew install platformio`  and  `brew install mosquitto_pub`.
2. install `platformio` extension
3. Edit WiFi Configuration and MQTT Configuration in `main.cpp` 
4. Compile and upload code to ESP32 and start monitoring with command  `pio run -e esp32dev --target upload && pio device monitor -b 115200`
5. You should see this in the terminal

```
========================= [SUCCESS] Took 19.65 seconds =========================
--- Terminal on /dev/cu.usbserial-0001 | 115200 8-N-1
--- Available filters and text transformations: colorize, debug, default, direct, esp32_exception_decoder, hexlify, log2file, nocontrol, printable, send_on_enter, time
--- More details at https://bit.ly/pio-monitor-filters
--- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H
================================================
🚀 Smart Lamp MQTT Test System Starting
   Version: 1.0 (Simulation Mode)
   Device: ESP32
================================================

🌐 Starting WiFi connection...
   SSID: FRITZ!Box 6591 Cable VG
.
✅ WiFi connected successfully!
   IP Address: 192.168.178.167
   Signal Strength: -34 dBm
================================================

✨ System initialization complete, waiting for MQTT connection...


🔌 Connecting to MQTT Broker...
   Server: 192.168.178.166:1883
   Client ID: ESP32Lamp-f26e
   ✅ MQTT connected successfully!
   📥 Subscribed to topic: smartlight/lamp/command

📤 Publishing state to MQTT:
   Topic: smartlight/lamp/state
   Message: {"state":"OFF","brightness":100,"color":{"r":255,"g":255,"b":255}}
   Result: ✅ Success
================================================
💡 Current Lamp State:
   Status: 🔴 OFF
   Brightness: 100%
   Color: RGB(255, 255, 255)
   Actual Output: Lamp is OFF
================================================
```

6. Send MQTT Control Commands 

```
 # example turn on the lamp with red color
   mosquitto_pub -h 192.168.178.166 -u xudong -P 112233 \
  -t smartlight/lamp/command \
  -m '{"state":"ON","brightness":100,"color":{"r":255,"g":0,"b":0}}'
```

7. Test  if the setting ist successful
```
pio device monitor -b 115200
```