//
// Created by Ray on 2020/11/25.
//

#ifndef EGTR_MATCH_UPPER_ICONTROLER_H
#define EGTR_MATCH_UPPER_ICONTROLER_H

#endif //EGTR_MATCH_UPPER_ICONTROLER_H

#include "controlerregister.h"

/*
 * @brief 控制器注册用宏定义，在类对应头文件类域中添加该宏定义
 */
#define CONRTOLER_DEF() \
public:                 \
    static IControl* getInstance(); \
    static controlerregister;

/*
 * @brief 控制器注册用宏定义，在类对应源文件中添加该宏定义
 * @parm controlername 控制器名称
 * @parm classname 控制器类名
 */
#define CONTROLER_REG(controlername,classname) \
IControler* className::getInstance(){\
    return new className();\
}\
ControlerRegister className::controlerregister(controlername,className::getInstance);

/*
 * @brief
 */
class IControlor{
public:
    IControlor()=default;
    virtual void already() = 0;
    virtual void processing(float deta) = 0;
    virtual ~IControlor()=default;
};