//
// Created by Ray on 2020/11/25.
//

#ifndef EGTR_MATCH_UPPER_BOTDEVICE_H
#define EGTR_MATCH_UPPER_BOTDEVICE_H

#include "serialportdevice.h"

/*
 * @brief 小车底盘串口控制类，继承自串口设备类，用于设置小车速度
 */
class BotDevice: public SerialPortDevice{
public:
    BotDevice();
    /*
     * @brief 设置小车底盘目标速度
     * @parm velocities 要设置的速度矢量{Vx,Vy,Vtheta}
     */
    void setTargetVelocity(std::vector<float> velocities);
private:

};


#endif //EGTR_MATCH_UPPER_BOTDEVICE_H
