//
// Created by Ray on 2020/11/16.
//

#ifndef LOWER_BOTMOTOR_H
#define LOWER_BOTMOTOR_H

#include "main.h"

/*
 *  @brief Enum for Motors which represents as four motors in bot
 */
typedef enum MotorPos{
    LEFT_FRONT,
    RIGHT_FRONT,
    LEFT_BACK,
    RIGHT_BACK
} MotorPos;

typedef struct MotorSpeed{
    int LeftFrontMotorSpeed;
    int RightFrontMotorSpeed;
    int LeftBackMotorSpeed;
    int RightBackMotorSpeed;
}MotorSpeed;

extern MotorSpeed motorSpeed;

void BotMotor_setMotorSpeed(MotorPos motorPos, int speed);

#endif //LOWER_BOTMOTOR_H
