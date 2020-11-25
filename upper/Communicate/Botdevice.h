//
// Created by Ray on 2020/11/25.
//

#ifndef EGTR_MATCH_UPPER_BOTDEVICE_H
#define EGTR_MATCH_UPPER_BOTDEVICE_H

#include "serialportdevice.h"

class Botdevice: public SerialPortDevice{
public:
    Botdevice();
    void setTargetVelocity(std::vector<float> velocities);
private:

};


#endif //EGTR_MATCH_UPPER_BOTDEVICE_H
