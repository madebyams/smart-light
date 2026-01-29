#ifndef RADAR_RGBSENSOR_H
#define RADAR_RGBSENSOR_H
#include <sstream>

#include "Config.hpp"
#include <SparkFunISL29125.hpp>

class rgb_sensor {
    SFE_ISL29125 rgb_sensor_;
public:
    struct color {
        uint16_t red;
        uint16_t green;
        uint16_t blue;

        std::string to_string();
    };

    struct color_buffer {
        uint16_t red[BUFFER_SIZE];
        uint16_t green[BUFFER_SIZE];
        uint16_t blue[BUFFER_SIZE];
    };

    explicit rgb_sensor(int address)
        : rgb_sensor_(address) {}

    void init();
    void measure(color_buffer* color_buffer, int position);
};

#endif //RADAR_RGBSENSOR_H