from pathlib import Path
import yaml

empty_environment = {
    "BUFFER_SIZE": 0,
    
    "WIFI": {
        "SSID": "",
        "PASSWORD": ""
    },

    "MQTT": {
        "SERVER": "",
        "PORT": 1883,
        "USER": "",
        "PASSWORD": "",
    
        "TOPICS": {
            "COMMAND": "",
            "STATE": ""
        }
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

if not Path("config.yml").exists():
    environment = empty_environment
else:
    environment = yaml.safe_load(open("config.yml", "r"))

with open("include/Config.h", "w") as config_header:
    config_header.write(render_define(environment))