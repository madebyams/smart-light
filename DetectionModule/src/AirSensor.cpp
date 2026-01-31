//
// Created by Amsakan on 15.01.26.
//
#include "AirSensor.hpp"

#include <Wire.h>

void air_sensor::init() {
    pinMode(FAILURE_LED, OUTPUT);

    Wire.begin();
    if (air_sensor_.begin() == false) {
        digitalWrite(FAILURE_LED, HIGH);
    }
}

void air_sensor::measure(data_buffer* data, int position) {
    data->co2[position] = air_sensor_.getCO2();
    data->temperature[position] = air_sensor_.getTemperature();
    data->humidity[position] = air_sensor_.getHumidity();
}

std::string air_sensor::data::to_string() {
    std::ostringstream json_stream{};

    json_stream << "{\n";
    json_stream << "\"co2\":" << co2 << ",\n";
    json_stream << "\"temperature\":" << temperature << ",\n";
    json_stream << "\"humidity\":" << humidity << "\n";
    json_stream << "}";

    return json_stream.str();
}
