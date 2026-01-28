//
// Created by Amsakan on 15.01.26.
//
#include "AirSensor.hpp"

#include <Wire.h>

void AirSensor::init() {
    pinMode(FAILURE_LED, OUTPUT);

    Wire.begin();
    if (my_air_sensor.begin() == false) {
        digitalWrite(FAILURE_LED, HIGH);
    }
}

void AirSensor::measure(DataBuffer* data, int position) {
    data->co2[position] = my_air_sensor.getCO2();
    data->temperature[position] = my_air_sensor.getTemperature();
    data->humidity[position] = my_air_sensor.getHumidity();
}


std::string AirSensor::Data::to_string() {
    std::ostringstream json_stream{};

    json_stream << "{\n";
    json_stream << "\"co2\":" << co2 << ",\n";
    json_stream << "\"temperature\":" << temperature << ",\n";
    json_stream << "\"humidity\":" << humidity << ",\n";
    json_stream << "}\n";

    return json_stream.str();
}