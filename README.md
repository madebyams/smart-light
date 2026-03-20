# IoT Smart Light

An IoT-based smart lighting system that uses environmental sensors to automatically control an RGB LED strip. Sensor data is processed by Home Assistant, which applies automation rules to adjust light state, color, and brightness based on presence, CO2 levels, ambient brightness, temperature, and noise.

## Authors

- Mathusan Saravanapavan
- Xudong Zhang
- Amsakan Bavan
- Yannic Hock

## Architecture

```
Environment (light, CO2, motion, noise)
        │
        ▼
DetectionModule (ESP32)          ← Reads all sensors
        │  MQTT: home/detection
        ▼
Home Assistant (Raspberry Pi)    ← Applies automation logic
        │  MQTT: home/ledstrip/set
        ▼
Lamp (ESP32)                     ← Controls LED strip
        │
        ▼
WS2801 RGB LED Strip
```

## Components

### DetectionModule

ESP32-based sensor array that publishes environmental data to MQTT every second.

**Sensors:**
| Sensor | Interface | Measures |
|---|---|---|
| DFRobot mmWave Radar | UART (GPIO 16/17) | Presence / motion |
| SparkFun SCD4x | I2C | CO2, temperature, humidity |
| LDR | ADC (GPIO 36) | Ambient brightness |
| RGB color sensor | I2C (0x44) | Ambient light color |
| MEMS microphone | ADC (GPIO 34) | Noise level |

**MQTT output topic:** `home/detection`

```json
{
  "brightness": 512,
  "noise_level": 130,
  "presence": true,
  "air_quality": { "co2": 850, "temperature": 22.5, "humidity": 45.0 },
  "light_color": { "r": 200, "g": 180, "b": 150 }
}
```

### Lamp

ESP32-based LED strip controller for a WS2801 RGB LED strip (default: 20 LEDs, data on GPIO 4).

**MQTT topics:**
- Subscribe: `home/ledstrip/set` — receives control commands
- Publish: `home/ledstrip/status` — reports current state

**Command format:**
```json
{ "state": "ON", "color": { "r": 255, "g": 100, "b": 0 }, "brightness": 200 }
```

### Home Assistant Automations

Located in `HomeAssistant/`. Each file is a Home Assistant automation YAML that reacts to sensor data:

| File | Behavior |
|---|---|
| `presence_dependent_light_control.yml` | Turn lights on/off based on presence |
| `co2_dependent_light_control.yml` | Adjust brightness based on CO2 level |
| `brightness_controlled_light_control.yml` | Auto-adjust brightness to ambient light |
| `temperature_dependent_light_control.yml` | Change color based on room temperature |
| `noise_dependent_light_control.yml` | React to noise level |

## Setup

### Prerequisites

- [PlatformIO](https://platformio.org/) (CLI or VS Code extension)
- Python 3.x
- MQTT broker (e.g., Mosquitto on Raspberry Pi with Home Assistant)

### Configuration

Both `DetectionModule` and `Lamp` use a JSON config file. A template is provided in each directory.

1. Copy and edit the config file:
   ```sh
   cp config.template.json config.json
   # edit config.json with your WiFi credentials, MQTT broker address, etc.
   ```

2. Generate the C++ config header:
   ```sh
   python include_config_header.py
   ```

3. Build and upload:
   ```sh
   pio run --target upload
   ```

### Monitoring

```sh
pio device monitor -b 115200
```

## CI/CD

GitLab CI pipeline (`.gitlab-ci.yml`) builds both modules on every push:
1. Installs PlatformIO
2. Generates config headers
3. Compiles with `pio run`

## MQTT Topics Summary

| Topic | Direction | Description |
|---|---|---|
| `home/detection` | DetectionModule → HA | Sensor data (JSON) |
| `home/ledstrip/set` | HA → Lamp | LED control commands |
| `home/ledstrip/status` | Lamp → HA | Current LED state |
