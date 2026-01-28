#ifndef RADAR_RGBSENSOR_H
#define RADAR_RGBSENSOR_H
#include <sstream>

#include "Defines.hh"
#include <SparkFunISL29125.h>

class RGBSensor {
    SFE_ISL29125 rgb_sensor;
public:
    struct Color {
        uint16_t red;
        uint16_t green;
        uint16_t blue;

        std::string to_string();
    };

    struct ColorBuffer {
        uint16_t red[BUFFER_SIZE];
        uint16_t green[BUFFER_SIZE];
        uint16_t blue[BUFFER_SIZE];
    };

    explicit RGBSensor(int address)
        : rgb_sensor(address) {}

    void init();
    void measure(ColorBuffer* color_buffer, int position);
};
#endif //RADAR_RGBSENSOR_H