//
// Created by Ray on 2020/12/9.
//

#include "serialcontrolor.h"
#include "motordriver.h"
#include <jansson.h>
#include <math.h>

#define pi ((double)3.1415926)
#define T2S(v) ((v/100.0f)*MAXSPEED)

float AXE_LEN = 0.145;
float THROTTLE;
float DIRECTION;
char* MOVEMODE;

void serialInfoHander(char* data,int length)
{
	json_error_t error;
	json_t *root;
	json_t *bot;
	MOVEMODE = NULL;
	root = json_loads(data,0,&error);
	if(!json_is_object(root)) return;
	bot = json_object_get(root,"bot");
	if(!json_is_object(bot)) return;
	
	THROTTLE = json_integer_value(json_object_get(bot,"throttle"));
	DIRECTION = json_integer_value(json_object_get(bot,"direction"));
	MOVEMODE = (char*)json_string_value(json_object_get(bot,"movemode"));
	
	if (NULL == MOVEMODE) return;
	if(strcmp(MOVEMODE,"translation") == 0){
		translation(THROTTLE,DIRECTION);
		free(MOVEMODE);
		return;
	}
	if(strcmp(MOVEMODE,"rotate") == 0){
		rotate(THROTTLE,DIRECTION);
		free(MOVEMODE);
		return;
	}
}

void translation(float throttle,float direction)
{
	float ax = T2S(throttle) * cos(pi*direction/180.0f);
	float ay = T2S(throttle) * sin(pi*direction/180.0f);
	
	MotorSpeed motorspeed;
	
	motorspeed.LeftFrontMotorSpeed  = ax + ay;
	motorspeed.RightFrontMotorSpeed = -ax + ay;
	motorspeed.LeftBackMotorSpeed   = ax + ay;
	motorspeed.RightBackMotorSpeed  = -ax + ay;

	setTargetSpeed_BotMotor(BOTMOTOR,&motorspeed);
}

void rotate(float throttle,float direction)
{
	MotorSpeed motorspeed;
	
	float v = (abs((int)direction)/(int)direction)*T2S(throttle)*AXE_LEN;
	
	motorspeed.LeftFrontMotorSpeed  = -v;
	motorspeed.RightFrontMotorSpeed = v;
	motorspeed.LeftBackMotorSpeed   = -v;
	motorspeed.RightBackMotorSpeed  = v;
	
	setTargetSpeed_BotMotor(BOTMOTOR,&motorspeed);
}
