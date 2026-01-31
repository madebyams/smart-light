//
// Created by Amsakan on 31.01.26.
//

#ifndef DETECTIONMODULE_COLOR_HPP
#define DETECTIONMODULE_COLOR_HPP
#include <cstdint>
#include <sstream>

#include "rgb_sensor.hpp"

struct color_t {
    uint16_t red;
    uint16_t green;
    uint16_t blue;

    std::string to_string() {
        std::ostringstream json_stream{};

        json_stream << "{\n";
        json_stream << "\"red\":" << red << ",\n";
        json_stream << "\"green\":" << green << ",\n";
        json_stream << "\"blue\":" << blue << "\n";
        json_stream << "}";

        return json_stream.str();
    }

    bool operator!=(const color_t& color) const {
        return
            red != color.red &&
            green != color.green &&
            blue != color.blue;
    }
};
#endif //DETECTIONMODULE_COLOR_HPP