//
// Created by Ray on 2020/11/16.
//

#include "botmotor.h"

#define ENCODER_VALUE2RAD(value) ((float)(value)/((13.0f)*(30.0f)) * (float)(6.283185307))


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

void getSampleSpeed_BotMotor(BotMotor botMotor,MotorSpeed* sampleSpeed){
    if(NULL == botMotor) return;
    ImpBotMotor* impBotMotor = (ImpBotMotor*)botMotor;
    memcpy(sampleSpeed,&(impBotMotor->sampleMotorSpeed),4*sizeof(float ));
}

void TIMSampleHander(BotMotor botMotor,float sampleTick){
    if(NULL == botMotor) return;
    ImpBotMotor* impBotMotor = (ImpBotMotor*)botMotor;
    //Sample encoder value
    int LeftFrontEncoderValue  = __HAL_TIM_GET_COUNTER(&htim5);
    int RightFrontEncoderValue = __HAL_TIM_GET_COUNTER(&htim3);
    int LeftBackEncoderValue   = __HAL_TIM_GET_COUNTER(&htim4);
    int RightBackEncoderValue  = __HAL_TIM_GET_COUNTER(&htim8);


    //convert encoder value to rad/s
    impBotMotor->sampleMotorSpeed.LeftFrontMotorSpeed  = (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim5) == 0 ? -1.0f :1.0f) * ENCODER_VALUE2RAD(LeftFrontEncoderValue)  / sampleTick;
    impBotMotor->sampleMotorSpeed.RightFrontMotorSpeed = (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3) == 0 ? -1.0f :1.0f) * ENCODER_VALUE2RAD(RightFrontEncoderValue) / sampleTick;
    impBotMotor->sampleMotorSpeed.LeftBackMotorSpeed   = (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4) == 0 ? -1.0f :1.0f) * ENCODER_VALUE2RAD(LeftBackEncoderValue)   / sampleTick;
    impBotMotor->sampleMotorSpeed.RightBackMotorSpeed  = (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim8) == 0 ? -1.0f :1.0f) * ENCODER_VALUE2RAD(RightBackEncoderValue)  / sampleTick;

    __HAL_TIM_SET_COUNTER(&htim5,0);
    __HAL_TIM_SET_COUNTER(&htim3,0);
    __HAL_TIM_SET_COUNTER(&htim4,0);
    __HAL_TIM_SET_COUNTER(&htim8,0);
}