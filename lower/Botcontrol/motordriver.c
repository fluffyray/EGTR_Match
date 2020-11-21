//
// Created by Ray on 2020/11/19.
//

#include "motordriver.h"


void TIMMotorDriverHander(){
    static PICalculator* PIcalculator = NULL;
    if (NULL == PIcalculator){
        PIcalculator = init_PICalculator(100,100,4);
    }

}