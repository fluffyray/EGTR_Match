//
// Created by Ray on 2020/12/9.
//

#include "serialcontrolor.h"
#include "motordriver.h"
#include "axedriver.h"
#include "GUI_Paint.h"
#include <jansson.h>
#include <math.h>

#define pi ((double)3.1415926)
#define T2S(v) ((v/100.0f)*MAXSPEED)

float AXE_LEN = 1.93;
float THROTTLE;
float DIRECTION;
char* MOVEMODE; 
char* INFODATA;

void serialInfoHander(char* data,int length)
{
	json_error_t error;
	json_t *root;
	json_t *bot;
	json_t *info;
	MOVEMODE = NULL;
	root = json_loads(data,0,&error);
	if(!json_is_object(root)) return;
	info = json_object_get(root,"bot");
	bot = json_object_get(root,"bot");
	if(json_is_object(bot))
	{
		THROTTLE = json_integer_value(json_object_get(bot,"throttle"));
		DIRECTION = json_integer_value(json_object_get(bot,"direction"));
		MOVEMODE = (char*)json_string_value(json_object_get(bot,"movemode"));
		json_delete(bot);
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
	if(json_is_object(info))
	{
		INFODATA = (char*)json_string_value(json_object_get(info,"data"));
		Paint_Clear(BLACK);
		Paint_DrawString_EN(16,16,INFODATA,&Font16,BLACK,WHITE);
	}
	json_delete(root);
//	axe = json_object_get(root,"axe");
//	if(!json_is_array(axe)) return;
	

	
//	int angSize = json_array_size(axe);
//	for(int i = 0;i < angSize && i < 6;++i)
//	{	
//		ANGSET[i] =  json_integer_value(json_array_get(axe,i));
//	}
	
	
	
//	json_delete(axe);

}

void translation(float throttle,float direction)
{
	float ax = T2S(throttle) * cos(pi*direction/180.0f);
	float ay = T2S(throttle) * sin(pi*direction/180.0f);
	
	MotorSpeed motorspeed;
	
	motorspeed.LeftFrontMotorSpeed  = ax + ay;
	motorspeed.RightFrontMotorSpeed = -ax + ay;
	motorspeed.LeftBackMotorSpeed   = -ax + ay;
	motorspeed.RightBackMotorSpeed  = ax + ay;

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
