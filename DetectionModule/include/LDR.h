//
// Created by Amsakan on 15.01.26.
//

#ifndef RADAR_LDR_H
#define RADAR_LDR_H
class LDR {
    int pin;
public:
    LDR(int pin) : pin(pin) {}
    void init();
    int measure();
};
#endif //RADAR_LDR_H