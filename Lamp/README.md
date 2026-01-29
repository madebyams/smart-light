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

1. `brew install platformio`  and  `brew install mosquitto_pub.
2. install `platformio` extension
3. Edit WiFi Configuration and MQTT Configuration in `lamp/main.cpp` 
4. Compile and upload code to ESP32 and start monitoring with command  `pio run --target upload && pio device monitor -b 115200`
5. You should see current LED status
6. Send MQTT Control Commands 

```c++
# red
mosquitto_pub -h 192.168.178.166 -u xudong -P 112233 \
  -t "home/ledstrip/set" \
  -m '{"state":"ON","color":{"r":255,"g":0,"b":0}}'

# green
mosquitto_pub -h 192.168.178.166 -u xudong -P 112233 \
  -t "home/ledstrip/set" \
  -m '{"state":"ON","color":{"r":0,"g":255,"b":0}}'

# lights off
mosquitto_pub -h 192.168.178.166 -u xudong -P 112233 \
  -t "home/ledstrip/set" \
  -m '{"state":"OFF"}'
```