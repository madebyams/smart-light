#ifndef RADAR_RGBSENSOR_H
#define RADAR_RGBSENSOR_H

#include <SparkFunISL29125.h>

namespace RGBSensor {
    struct Color {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    class RGBSensor {
        SFE_ISL29125 rgb_sensor;
    public:
        void init();
        Color measure();
    };
}
#endif //RADAR_RGBSENSOR_H