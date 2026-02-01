//
// Created by Amsakan on 31.01.26.
//

#ifndef LAMP_SETTING_HPP
#define LAMP_SETTING_HPP

#include "color.hpp"
#include "ArduinoJson.h"

struct setting_t {
    std::string id;
    std::string state;
    std::string mode;
    color_t color;
    uint8_t brightness;

    std::function<void (std::string)> on_id = {};
    std::function<void (std::string)> on_state = {};
    std::function<void (std::string)> on_mode = {};
    std::function<void (color_t)> on_color = {};
    std::function<void (uint8_t)> on_brightness = {};

    static setting_t from_mqtt_payload(std::uint8_t* payload, std::size_t length) {
        std::string message(reinterpret_cast<char*>(payload), length);
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, message);

        return {
            doc["id"],
        doc["state"],
        doc["mode"],
        {
                .red = static_cast<uint8_t>(doc["color"]["r"] | 0),
                .green = static_cast<uint8_t>(doc["color"]["g"] | 0),
                .blue = static_cast<uint8_t>(doc["color"]["b"] | 0),
                .white = static_cast<uint8_t>(doc["color"]["w"] | 0)
            },
            doc["brightness"]
        };
    }

    void apply() const {
        on_id(id);
        on_state(state);
        on_mode(mode);
        on_color(color);
        on_brightness(brightness);
    }
};
#endif //LAMP_SETTING_HPP