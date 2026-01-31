#ifndef RADAR_RGBSENSOR_H
#define RADAR_RGBSENSOR_H
#include <SparkFunISL29125.hpp>


#include "color.hpp"

class rgb_sensor {
public:
    using color = color_t;

    explicit rgb_sensor(int address)
        : rgb_sensor_(address) {}

    void init();
    color measure();
private:
    SFE_ISL29125 rgb_sensor_;
    color last_measurement_;
};

#endif //RADAR_RGBSENSOR_H