//
// Created by Ray on 2020/11/20.
//

#include "picalculator.h"

typedef struct ImpPICalculator{
    int parmP;
    int parmI;
    int valueSize;
    int* PbiasValue;
}ImpPICalculator;

PICalculator init_PICalculator(int parmP,int parmI,int valueSize){
    ImpPICalculator* PIcalculator = (ImpPICalculator*)malloc(sizeof(struct ImpPICalculator));
    PIcalculator->parmI = parmI;
    PIcalculator->parmP = parmP;
    PIcalculator->PbiasValue = (int*)malloc(valueSize * sizeof(int));
    memset(PIcalculator->PbiasValue, 0, valueSize * sizeof(int));

    return PIcalculator;
}

void getResults_PICalculator(PICalculator piCalculator,int* targetValue,int* sampleValue,int* value){
    if (NULL == piCalculator) return;
    ImpPICalculator* ImpPIcalculator = (ImpPICalculator*) piCalculator;
    int* Cbias = (int*)malloc(ImpPIcalculator->valueSize*sizeof(int));
    for (int i = 0; i < ImpPIcalculator->valueSize-1; ++i) {
        Cbias[i] = targetValue[i] - sampleValue[i];
        value[i] =ImpPIcalculator->parmP*(Cbias[i] - ImpPIcalculator->PbiasValue[i])
                  + ImpPIcalculator->parmI*Cbias[i]; //calculate value
    }
    memcpy(ImpPIcalculator->PbiasValue,Cbias,ImpPIcalculator->valueSize*sizeof(int));// save bias
    free(Cbias);
    Cbias = NULL;
}

void changePrams_PICalculator(PICalculator piCalculator,int parmP,int parmI){
    if (NULL == piCalculator) return;
    ImpPICalculator* ImpPIcalculator = (ImpPICalculator*) piCalculator;
    ImpPIcalculator->parmP = parmP;
    ImpPIcalculator->parmI = parmI;
}

void delete_PICalculator(PICalculator piCalculator){
    if (NULL == piCalculator) return;
    ImpPICalculator* ImpPIcalculator = (ImpPICalculator*) piCalculator;
    free(ImpPIcalculator->PbiasValue);
    ImpPIcalculator->PbiasValue = NULL;
    free(ImpPIcalculator);
}