//
// Created by Ray on 2020/11/19.
//

#include "motordriver.h"

#define STRENGTH2PWM(value) value*1

void TIMMotorDriverHander(){
    static PICalculator* PIcalculator = NULL;
    if (NULL == PIcalculator){
        PIcalculator = init_PICalculator(100,100,MOTORNUM);
    }
    MotorSpeed targetSpeed;
    MotorSpeed sampleSpeed;
    getSampleSpeed_BotMotor(BOTMOTOR,&sampleSpeed);
    getTargetSpeed_BotMotor(BOTMOTOR,&targetSpeed);
    float speedStrength[MOTORNUM];
    getResults_PICalculator(PIcalculator,&targetSpeed,&sampleSpeed,&speedStrength);
    unsigned char isPositive[MOTORNUM];
    for (int i = 0; i <MOTORNUM-1; ++i) {
        isPositive[i] = speedStrength > 0;
    }

    //motor direction
    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,!isPositive[0]);//FrontLIN1
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,isPositive[0]);//FrontLIN2

    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,!isPositive[1]);//FrontRIN1
    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,isPositive[1]);//FrontRIN2

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,!isPositive[2]);//BackLIN1
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,isPositive[2]);//BackLIN2

    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,!isPositive[3]);//BackRIN1
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,isPositive[3]);//BackRIN2

    //motor current strength
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,STRENGTH2PWM(speedStrength[0]));
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,STRENGTH2PWM(speedStrength[1]));
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,STRENGTH2PWM(speedStrength[2]));
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,STRENGTH2PWM(speedStrength[3]));


}