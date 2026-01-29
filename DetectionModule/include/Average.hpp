//
// Created by Amsakan on 28.01.26.
//

#ifndef DETECTIONMODULE_AVERAGE_HH
#define DETECTIONMODULE_AVERAGE_HH
#include <cstdint>
#include "AirSensor.hpp"
#include "RGBSensor.hpp"

namespace average {
    int calculate_average(int* data, uint32_t size);
    bool calculate_average(bool* data, uint32_t size);
    air_sensor::data calculate_average(air_sensor::data_buffer* data, uint32_t size);
    rgb_sensor::color calculate_average(rgb_sensor::color_buffer* data, uint32_t size);
}

template<typename T>
void sort(T* arr, int size) {
    for (int i = 1; i < size; ++i) {
        T key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

#endif //DETECTIONMODULE_MEDIAN_HH