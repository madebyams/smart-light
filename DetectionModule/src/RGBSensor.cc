#include <Arduino.h>
#include "RGBSensor.h"


void RGBSensor::init() {
    if (!rgb_sensor.init()) {
        Serial.println("Failed to init RGB module!");
        while(true) {;;}
    }
}

void RGBSensor::measure(ColorBuffer* color_buffer, int position) {
    color_buffer->red[position] = rgb_sensor.readRed();
    color_buffer->green[position] = rgb_sensor.readGreen();
    color_buffer->blue[position] = rgb_sensor.readBlue();
}

std::string RGBSensor::Color::to_string() {
    std::ostringstream json_stream{};

    json_stream << "{\n";
    json_stream << "\"red\":" << red << ",\n";
    json_stream << "\"green\":" << green << ",\n";
    json_stream << "\"blue\":" << blue << ",\n";
    json_stream << "}\n";

    return json_stream.str();
}
