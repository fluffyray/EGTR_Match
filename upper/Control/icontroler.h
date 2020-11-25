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
 * @brief 控制器接口，所有控制器实现该接口,并使用以上两个宏定义
 */
class IControlor{
public:

    /*
     * @brief 在控制器初始化时，该函数会被调用
     */
    virtual void already() = 0;

    /*
     * @brief 在系统每个控制周期中，该函数会被调用
     */
    virtual void processing(float deta) = 0;

    IControlor()=default;
    virtual ~IControlor()=default;
};