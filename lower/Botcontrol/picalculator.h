//
// Created by Ray on 2020/11/16.
//

#ifndef LOWER_PICALCULATOR_H
#define LOWER_PICALCULATOR_H

#include "stdlib.h"
#include "string.h"

typedef void* PICalculator;

void getResults_PICalculator(PICalculator piCalculator,const float* targetValue,const float* sampleValue,float* value);

void changePrams_PICalculator(PICalculator piCalculator,float parmP,float parmI);

void delete_PICalculator(PICalculator piCalculator);

PICalculator init_PICalculator(float parmP,float parmI,int valueSize);
#endif //LOWER_PICALCULATOR_H
