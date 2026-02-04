//
// Created by Amsakan on 15.01.26.
//

#ifndef RADAR_MIC_H
#define RADAR_MIC_H
#include "config.hpp"

class mic {
    int pin_;
    int last_measurement_ = 0;

    static constexpr int NUM_SAMPLES = (MIC_SAMPLE_RATE * MIC_WINDOW_MS) / 1000;
    int ADC_MAX = (1 << MIC_ADC_BITS) - 1;

public:
    explicit mic(int pin) : pin_(pin) {}
    void init();
    int measure();
};

#endif // RADAR_MIC_H
