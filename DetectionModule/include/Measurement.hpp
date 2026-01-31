//
// Created by Amsakan on 29.01.26.
//

#ifndef DETECTIONMODULE_MEASUREMENT_HPP
#define DETECTIONMODULE_MEASUREMENT_HPP
#include <sstream>

#include "AirSensor.hpp"
#include "RGBSensor.hpp"

struct measurement {
    int brightness;
    int noise_level;
    bool presence;
    air_sensor::data air_quality;
    rgb_sensor::color light_color;

    inline std::string to_string() {
        std::ostringstream json_stream;

        json_stream << "{\n";
        json_stream << "\"brightness\":" << brightness << ",\n";
        json_stream << "\"noise_level\":" << noise_level << ",\n";
        json_stream << "\"presence\":" << presence << ",\n";
        json_stream << "\"air_quality\":" << air_quality.to_string() << ",\n";
        json_stream << "\"light_color\":" << light_color.to_string() << "\n";
        json_stream << "}\n";

        return json_stream.str();
    }
};
#endif //DETECTIONMODULE_MEASUREMENT_HPP