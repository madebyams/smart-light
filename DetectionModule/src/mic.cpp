//
// Created by Amsakan on 15.01.26.
//
#include "mic.hpp"

#include <Arduino.h>

void mic::init() {
    pinMode(pin_, INPUT);

    analogReadResolution(MIC_ADC_BITS);
    analogSetPinAttenuation(pin_, ADC_11db);
}

int mic::measure() {
    uint32_t sum = 0;
    int minV = ADC_MAX;
    int maxV = 0;
    const uint32_t samplePeriodUs = 1000000UL / MIC_SAMPLE_RATE;
    int samples[NUM_SAMPLES] = {};
    uint32_t t = micros();

    for (int & sample : samples) {
        // Timing (simple)
        while ((micros() - t) < samplePeriodUs){}
        t += samplePeriodUs;

        int v = analogRead(pin_);
        sample = v;

        sum += v;
        if (v < minV)
            minV = v;
        if (v > maxV)
            maxV = v;
    }

    float mean = static_cast<float>(sum) / static_cast<float>(NUM_SAMPLES);

    // RMS der AC-Komponente (ohne DC offset)
    double accSq = 0.0;
    for (int sample : samples) {
        float ac = static_cast<float>(sample) - mean;
        accSq += static_cast<double>(ac) * static_cast<double>(ac);
    }

    auto rms = static_cast<float>(sqrt(accSq / static_cast<double>(NUM_SAMPLES)));


    float rmsForDb = max(rms, 1.0f);
    float pseudoDb = 20.0f * log10(rmsForDb);


    return pseudoDb;
}
