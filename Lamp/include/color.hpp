//
// Created by Amsakan on 01.02.26.
//

#ifndef LAMP_COLOR_HPP
#define LAMP_COLOR_HPP

struct color_t {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t white;

    static color_t hsvToRgb(uint16_t hue, uint8_t saturation, uint8_t value) {
        hue = hue % 360;
        float h = static_cast<float>(hue) / 60.0f;
        float s = static_cast<float>(saturation) / 255.0f;
        float v = static_cast<float>(value) / 255.0f;

        int i = static_cast<int>(h);
        float f = h - i;
        float p = v * (1.0f - s);
        float q = v * (1.0f - s * f);
        float t = v * (1.0f - s * (1.0f - f));

        float rf, gf, bf;
        switch (i % 6) {
        case 0:
            rf = v;
            gf = t;
            bf = p;
            break;
        case 1:
            rf = q;
            gf = v;
            bf = p;
            break;
        case 2:
            rf = p;
            gf = v;
            bf = t;
            break;
        case 3:
            rf = p;
            gf = q;
            bf = v;
            break;
        case 4:
            rf = t;
            gf = p;
            bf = v;
            break;
        default:
            rf = v;
            gf = p;
            bf = q;
            break;
        }

        return {
            .red = static_cast<uint8_t>(rf * 255),
            .green = static_cast<uint8_t>(gf * 255),
            .blue = static_cast<uint8_t>(bf * 255)
        };
    }

};

#endif //LAMP_COLOR_HPP