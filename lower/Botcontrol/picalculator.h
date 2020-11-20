//
// Created by Ray on 2020/11/16.
//

#ifndef LOWER_PICALCULATOR_H
#define LOWER_PICALCULATOR_H

#include "stdlib.h"
#include "string.h"

typedef void* PICalculator;

void getResults_PICalculator(PICalculator piCalculator,int* targetValue,int* sampleValue,int* value);

void changePrams_PICalculator(PICalculator piCalculator,int parmP,int parmI);

void delete_PICalculator(PICalculator piCalculator);

PICalculator init_PICalculator(int parmP,int parmI,int valueSize);
#endif //LOWER_PICALCULATOR_H
