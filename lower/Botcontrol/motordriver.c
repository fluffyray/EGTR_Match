//
// Created by Ray on 2020/11/19.
//

#include "motordriver.h"

#define STRENGTH2PWM(value) value
float speedStrength[4];
void TIMMotorDriverHander(){
    static PICalculator* PIcalculator = NULL;
    if (NULL == PIcalculator){
        PIcalculator = init_PICalculator(12,5,MOTORNUM);
    }
    MotorSpeed targetSpeed;
    MotorSpeed sampleSpeed;
    getSampleSpeed_BotMotor(BOTMOTOR,&sampleSpeed);
    getTargetSpeed_BotMotor(BOTMOTOR,&targetSpeed);
		
    getResults_PICalculator(PIcalculator,(const float * )&targetSpeed,(const float * )&sampleSpeed,speedStrength);
		//memcpy(speedStrength,&targetSpeed,sizeof(float)*4);
		
    unsigned char isPositive[MOTORNUM+1];
    for (int i = 0; i <MOTORNUM; ++i) {
			isPositive[i] = speedStrength[i] > 0;
			isPositive[i]==0 ?  (speedStrength[i] = -speedStrength[i]):0;
    }

    //motor direction
    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,isPositive[0]);//FrontLIN1
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,!isPositive[0]);//FrontLIN2

    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,!isPositive[1]);//FrontRIN1
    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,isPositive[1]);//FrontRIN2

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,isPositive[2]);//BackLIN1
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,!isPositive[2]);//BackLIN2

    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,!isPositive[3]);//BackRIN1
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,isPositive[3]);//BackRIN2

    //motor current strength
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,STRENGTH2PWM(speedStrength[0]));
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,STRENGTH2PWM(speedStrength[1]));
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,STRENGTH2PWM(speedStrength[2]));
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,STRENGTH2PWM(speedStrength[3]));


}
