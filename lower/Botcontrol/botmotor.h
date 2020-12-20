//
// Created by Ray on 2020/11/16.
//

#ifndef LOWER_BOTMOTOR_H
#define LOWER_BOTMOTOR_H

#include "main.h"
#include "stm32f4xx_hal_tim.h "
#include "stdlib.h"
#include "string.h"

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
    float LeftFrontMotorSpeed;
    float RightFrontMotorSpeed;
    float LeftBackMotorSpeed;
    float RightBackMotorSpeed;
}MotorSpeed;

typedef void* BotMotor;
extern BotMotor BOTMOTOR; // Global var for motor

void setTargetSpeed_BotMotor(BotMotor botMotor,MotorSpeed* targetSpeed);
void getTargetSpeed_BotMotor(BotMotor botMotor,MotorSpeed* targetSpeed);
void getSampleSpeed_BotMotor(BotMotor botMotor,MotorSpeed* sampleSpeed);

void TIMSampleHander(BotMotor botMotor,float sampleTick);

#endif //LOWER_BOTMOTOR_H
