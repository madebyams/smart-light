//
// Created by Amsakan on 28.01.26.
//
#include "Average.hpp"

int Average::calulcate_average(int* data, uint32_t size) {
    sort(data, size);

    return (1/2) * (data[size / 2] + data[(size / 2) + 1]);
}

AirSensor::Data Average::calculate_average(AirSensor::DataBuffer* data, uint32_t size) {
    sort(data->co2, size);
    sort(data->humidity, size);
    sort(data->temperature, size);

    return {
        .co2 = static_cast<uint16_t>((1/2) * (data->co2[size / 2] + data->co2[(size / 2) + 1])),
        .temperature = (1.0f/2.0f) * (data->temperature[size / 2] + data->temperature[(size / 2) + 1]),
        .humidity = (1.0f/2.0f) * (data->humidity[size / 2] + data->humidity[(size / 2) + 1])
    };
}

RGBSensor::Color Average::calculate_average(RGBSensor::ColorBuffer* data, uint32_t size) {
    sort(data->red, size);
    sort(data->green, size);
    sort(data->blue, size);

    return {
        .red = static_cast<uint16_t>((1/2) * (data->red[size / 2] + data->red[(size / 2) + 1])),
        .green = static_cast<uint16_t>((1/2) * (data->green[size / 2] + data->green[(size / 2) + 1])),
        .blue = static_cast<uint16_t>((1/2) * (data->blue[size / 2] + data->blue[(size / 2) + 1])),
    };
}
