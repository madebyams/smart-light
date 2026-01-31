//
// Created by Amsakan on 31.01.26.
//

#ifndef LAMP_SETTING_HPP
#define LAMP_SETTING_HPP
struct color_t {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t white;
};

struct setting_t {
    std::string id;
    std::string state;
    std::string mode;
    color_t color;
    uint8_t brightness;
};
#endif //LAMP_SETTING_HPP