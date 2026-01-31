//
// Created by Amsakan on 15.01.26.
//

#ifndef RADAR_MIC_H
#define RADAR_MIC_H

class mic {
    int pin_;
    int last_measurement = 0;
public:
    explicit mic(int pin) : pin_(pin) {}
    void init();
    int measure();
};

#endif // RADAR_MIC_H
