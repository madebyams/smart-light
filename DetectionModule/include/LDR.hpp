//
// Created by Amsakan on 15.01.26.
//

#ifndef RADAR_LDR_H
#define RADAR_LDR_H
class ldr {
    int pin_;
public:
    explicit ldr(int pin) : pin_(pin) {}
    void init();
    int measure();
};

#endif //RADAR_LDR_H