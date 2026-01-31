//
// Created by Amsakan on 31.01.26.
//

#ifndef DETECTIONMODULE_DATA_HPP
#define DETECTIONMODULE_DATA_HPP
#include <cstdint>
#include <string>

struct data_t {
    uint16_t co2;
    float temperature;
    float humidity;

    std::string to_string() {
        std::ostringstream json_stream{};

        json_stream << "{\n";
        json_stream << "\"co2\":" << co2 << ",\n";
        json_stream << "\"temperature\":" << temperature << ",\n";
        json_stream << "\"humidity\":" << humidity << "\n";
        json_stream << "}";

        return json_stream.str();
    }


    bool operator!=(const data_t& data) const {
        return
            co2 != data.co2
            && temperature != data.temperature
            && humidity != data.humidity;
    }
};
#endif //DETECTIONMODULE_DATA_HPP