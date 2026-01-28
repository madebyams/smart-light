//
// Created by Amsakan on 28.01.26.
//

#ifndef DETECTIONMODULE_AVERAGE_HH
#define DETECTIONMODULE_AVERAGE_HH
#include <cstdint>
#include "AirSensor.hpp"
#include "RGBSensor.hpp"

namespace Average {
    int calulcate_average(int* data, uint32_t size);
    AirSensor::Data calculate_average(AirSensor::DataBuffer* data, uint32_t size);
    RGBSensor::Color calculate_average(RGBSensor::ColorBuffer* data, uint32_t size);
}

template<typename T>
void sort(T* arr, int n) {
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
#endif //DETECTIONMODULE_MEDIAN_HH