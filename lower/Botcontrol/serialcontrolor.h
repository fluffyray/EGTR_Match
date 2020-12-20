//
// Created by Ray on 2020/12/9.
//

#ifndef LOWER_SERIALCONTROLOR_H
#define LOWER_SERIALCONTROLOR_H
#include "botmotor.h"


void serialInfoHander(char* data,int length);
void translation(float throttle,float direction);
void rotate(float throttle,float direction);

#endif //LOWER_SERIALCONTROLOR_H
