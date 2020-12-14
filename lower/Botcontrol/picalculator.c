//
// Created by Ray on 2020/11/20.
//

#include "picalculator.h"

typedef struct ImpPICalculator{
    float parmP;
    float parmI;
    int valueSize;
    float * PbiasValue;
}ImpPICalculator;

PICalculator init_PICalculator(float parmP,float parmI,int valueSize){
    ImpPICalculator* PIcalculator = (ImpPICalculator*)malloc(sizeof(struct ImpPICalculator));
    PIcalculator->parmI = parmI;
    PIcalculator->parmP = parmP;
    PIcalculator->PbiasValue = (float *)malloc(valueSize * sizeof(float ));
    memset(PIcalculator->PbiasValue, 0, valueSize * sizeof(float ));
    return PIcalculator;
}

void getResults_PICalculator(PICalculator piCalculator,const float * targetValue,const float * sampleValue,float * value){
    if (NULL == piCalculator) return;
    ImpPICalculator* impPIcalculator = (ImpPICalculator*) piCalculator;
    float * Cbias = (float *)malloc(impPIcalculator->valueSize * sizeof(float ));
    for (int i = 0; i < impPIcalculator->valueSize - 1; ++i) {
        Cbias[i] = targetValue[i] - sampleValue[i];
        value[i] += impPIcalculator->parmP * (Cbias[i] - impPIcalculator->PbiasValue[i])
                   + impPIcalculator->parmI * Cbias[i]; //calculate value
    }
    memcpy(impPIcalculator->PbiasValue, Cbias, impPIcalculator->valueSize * sizeof(float ));// save bias
    free(Cbias);
    Cbias = NULL;
}

void changePrams_PICalculator(PICalculator piCalculator,float parmP,float parmI){
    if (NULL == piCalculator) return;
    ImpPICalculator* impPIcalculator = (ImpPICalculator*) piCalculator;
    impPIcalculator->parmP = parmP;
    impPIcalculator->parmI = parmI;
}

void delete_PICalculator(PICalculator piCalculator){
    if (NULL == piCalculator) return;
    ImpPICalculator* impPIcalculator = (ImpPICalculator*) piCalculator;
    free(impPIcalculator->PbiasValue);
    impPIcalculator->PbiasValue = NULL;
    free(impPIcalculator);
}