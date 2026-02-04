from pathlib import Path
import json

empty_environment = {
    "BUFFER_SIZE": 50,
    
    "GPIO": {
        "STATUS_LED": 2,
        "LDR": 15,
        "MIC": 26
    },

    "WIFI": {
        "SSID": "",
        "PASSWORD": ""
    },

    "MQTT": {
        "SERVER": "",
        "PORT": 1883,
        "DEVICE_ID": "",
        "USER": "",
        "PASSWORD": "",

        "CONNECTION_ATTEMPTS": 5,
    
        "TOPICS": {
            "MEASUREMENT_DATA": ""
        }
    },

    "MIC": {
        "SAMPLE_RATE": 8000,
        "WINDOW_MS": 100,
        "ADC_BITS": 12
    }
}


def get_define_tree(config_tree, prefix=""):
    result = ""
    for key in config_tree:
        if isinstance(config_tree[key], dict):
            result += get_define_tree(config_tree[key], prefix+f"{key}_")
        else:
            if isinstance(config_tree[key], int):
                result +=  f"#define {prefix}{key} {config_tree[key]}\n"
            else:
                result +=  f'#define {prefix}{key} "{config_tree[key]}"\n'
    
    return result

def render_define(config):
    result = "#ifndef RESULT_H\n"
    result += "#define RESULT_H\n"
    result += get_define_tree(config)
    result += "#endif"

    return result

if not Path("config.json").exists():
    environment = empty_environment
else:
    environment = json.loads(open("config.json", "r").read())

with open("include/config.hpp", "w") as config_header:
    config_header.write(render_define(environment))