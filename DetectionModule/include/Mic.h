//
// Created by Amsakan on 15.01.26.
//

#ifndef RADAR_MIC_H
#define RADAR_MIC_H
class Mic {
    int pin;
public:
    Mic(int pin) : pin(pin) {}
    void init();
    int measure();
};
#endif //RADAR_MIC_H