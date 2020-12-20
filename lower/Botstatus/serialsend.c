#include <jansson.h>
#include "main.h"
#include "stm32f4xx_hal_uart.h"
#include "botmotor.h"
#include "stdio.h"


void TIMSerialSendHander()
{
	char info[128];
	MotorSpeed speed;
	getSampleSpeed_BotMotor(BOTMOTOR,&speed);
	sprintf(info,"\n\n[1]: %f\n[2]: %f\n[3]: %f\n[4]: %f\n\n\n",speed.LeftFrontMotorSpeed,speed.RightFrontMotorSpeed,speed.LeftBackMotorSpeed,speed.RightBackMotorSpeed);
	HAL_UART_Transmit(&huart1,info,strlen(info)+1,10000);
}