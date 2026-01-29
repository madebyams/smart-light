#include <Arduino.h>
#include "RGBSensor.hpp"


void rgb_sensor::init() {
    if (!rgb_sensor_.init()) {
        Serial.println("Failed to init RGB module!");
        while (true) { ;; }
    }
}

void rgb_sensor::measure(color_buffer* color_buffer, int position) {
    color_buffer->red[position] = rgb_sensor_.readRed();
    color_buffer->green[position] = rgb_sensor_.readGreen();
    color_buffer->blue[position] = rgb_sensor_.readBlue();
}

std::string rgb_sensor::color::to_string() {
    std::ostringstream json_stream{};

    json_stream << "{\n";
    json_stream << "\"red\":" << red << ",\n";
    json_stream << "\"green\":" << green << ",\n";
    json_stream << "\"blue\":" << blue << "\n";
    json_stream << "}\n";

    return json_stream.str();
}
