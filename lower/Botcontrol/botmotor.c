//
// Created by Ray on 2020/11/16.
//

#include "botmotor.h"

typedef struct MotorPWM{
    int LeftFrontMotorPWM;
    int RightFrontMotorPWM;
    int LeftBackMotorPWM;
    int RightBackMotorPWM;
}MotorPWM;

MotorSpeed motorSpeed;
MotorPWM motorPWM;

void BotMotor_setMotorSpeed(MotorPos motorPos, int speed){
    *((int*)(&motorSpeed) + motorPos) = speed;
    *((int*)(&motorPWM) + motorPos) = speed;//TODO: translate integrated speed into specific PWM value

}

