//
// Created by Ray on 2020/11/16.
//

#include "botmotor.h"

#define ENCODER_VALUE2RAD(value) ((float)(value)/((13.0f)*(30.0f)) * (float)(6.283185307))

BotMotor BOTMOTOR;

typedef struct ImpBotMotor {
    MotorSpeed targetMotorSpeed;
    MotorSpeed sampleMotorSpeed;

}ImpBotMotor;

ImpBotMotor IMPBOTMOTOR = {{0,0,0,0},{0,0,0,0}};
BotMotor BOTMOTOR = &IMPBOTMOTOR;


void setTargetSpeed_BotMotor(BotMotor botMotor,MotorSpeed* targetSpeed){
    if(NULL == botMotor) return;
    ImpBotMotor* impBotMotor = (ImpBotMotor*)botMotor;
    memcpy(&(impBotMotor->targetMotorSpeed),targetSpeed,4*sizeof(float ));

}

void getTargetSpeed_BotMotor(BotMotor botMotor,MotorSpeed* targetSpeed){
    if(NULL == botMotor) return;
    ImpBotMotor* impBotMotor = (ImpBotMotor*)botMotor;
    memcpy(targetSpeed,&(impBotMotor->targetMotorSpeed),4*sizeof(float ));
}

void getSampleSpeed_BotMotor(BotMotor botMotor,MotorSpeed* sampleSpeed){
    if(NULL == botMotor) return;
    ImpBotMotor* impBotMotor = (ImpBotMotor*)botMotor;
    memcpy(sampleSpeed,&(impBotMotor->sampleMotorSpeed),4*sizeof(float ));
}

void TIMSampleHander(BotMotor botMotor,float sampleTick){
    if(NULL == botMotor) return;
    ImpBotMotor* impBotMotor = (ImpBotMotor*)botMotor;
		
    //Sample encoder value
		int LeftFrontEncoderValue     = -(short)__HAL_TIM_GET_COUNTER(&htim5);
    int RightFrontEncoderValue = (short)__HAL_TIM_GET_COUNTER(&htim3);
    int LeftBackEncoderValue   = -(short)__HAL_TIM_GET_COUNTER(&htim4);
    int RightBackEncoderValue  = (short)__HAL_TIM_GET_COUNTER(&htim8);


    //convert encoder value to rad/s
    impBotMotor->sampleMotorSpeed.LeftFrontMotorSpeed  = ENCODER_VALUE2RAD(LeftFrontEncoderValue)  / sampleTick;
    impBotMotor->sampleMotorSpeed.RightFrontMotorSpeed = ENCODER_VALUE2RAD(RightFrontEncoderValue) / sampleTick;
    impBotMotor->sampleMotorSpeed.LeftBackMotorSpeed   = ENCODER_VALUE2RAD(LeftBackEncoderValue)   / sampleTick;
    impBotMotor->sampleMotorSpeed.RightBackMotorSpeed  = ENCODER_VALUE2RAD(RightBackEncoderValue)  / sampleTick;

    __HAL_TIM_SET_COUNTER(&htim5,0);
    __HAL_TIM_SET_COUNTER(&htim3,0);
    __HAL_TIM_SET_COUNTER(&htim4,0);
    __HAL_TIM_SET_COUNTER(&htim8,0);
}