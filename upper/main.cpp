//
// Created by peng chen on 2020/12/19.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "json.hpp"
#include <unistd.h>
#include "wiringSerial.h"


using json = nlohmann::json;
using namespace std;

int throttle=0;//油门量，初始速度为0
int direction= 270;//方向，初始方向为正前方
string movemode = "translation";//移动模式，初始为平动
int axe[5] = {37,513,409,425,880};//舵机移动角度，初始为静止状态
char *out=NULL;//json文件字符，初始为空
int fd;

void initSpeed();//速度
void changeSpeed();//改变速度
void stopMove();//停下小车
void waytoDrive();//方向
void changeWaytoDrive();//改变方向
void initMode();//移动模式
void modeChange();//移动模式切换
void qrcodeAndColorIdentify();//二维码和颜色识别
void jsonCreated();//json文本生成类
//1~3分别是从右到左，物料放置处

void axeInit();//初始化
    void axeCatchSpace();//抓取位置
        void axeLoad1();//放置位置1
            void axeLoad2();//放置位置2
                void axeLoad3();//放置位置3
                    void axeCatch();;//抓取动作
                        void axePut();//放置动作

void initSpeed(){//初始化速度
    throttle=15;
}

void changeSpeed(){//改变初始速度与转动速度
    if(movemode=="translation"){
        throttle=15;
    }
    else if(movemode=="rotate"){
        throttle=15;
    }
}

void stopMove(){//停下小车
    throttle=0;
}

void waytoDrive(){//初始化前进方向
    direction= 90;
}

void changeWaytoDrive(){//改变前进方向
    direction= 180;
}

void rotatetoDirection(){//旋转时方向
    direction= -90;
}

void initMode(){//初始化移动模式
    movemode="translation";
}

void modeChange(){//改变移动模式方法
    if(movemode=="translation"){
        movemode="rotate";
    }
    else if(movemode=="rotate"){
        movemode="translation";
    }
}

void axeInit(){//初始化
    axe[0]=497;
    axe[1]=669;
    axe[2]=24308;
    axe[3]=34446;
    axe[4]=880;
    jsonCreated();
    serialPuts(fd,out);
}

void axeCatchSpaceRed(){//抓取位置红
    axe[0]=741;
    axe[1]=409;
    axe[2]=52;
    axe[3]=438;
    jsonCreated();
    serialPuts(fd,out);
}

void axeCatchSpaceGreen(){//抓取位置绿
    axe[0]=831;
    axe[1]=566;
    axe[2]=300;
    axe[3]=442;
    jsonCreated();
    serialPuts(fd,out);
}
void axeCatchSpaceBlue(){//抓取位置蓝
    axe[0]=992;
    axe[1]=515;
    axe[2]=390;
    axe[3]=441;
    jsonCreated();
    serialPuts(fd,out);
}

void axeWaitRed(){//悬空位置红
    axe[0]=714;
    axe[1]=669;
    axe[2]=24308;
    axe[3]=34446;
    jsonCreated();
    serialPuts(fd,out);
}

void axeWaitGreen(){//悬空位置绿
    axe[0]=831;
    axe[1]=669;
    axe[2]=24308;
    axe[3]=34446;
    jsonCreated();
    serialPuts(fd,out);
}

void axeWaitBlue(){//悬空位置蓝
    axe[0]=992;
    axe[1]=669;
    axe[2]=24308;
    axe[3]=34446;
    jsonCreated();
    serialPuts(fd,out);
}

void axeLoad1(){//放置位置红右
    axe[0]=620;
    axe[1]=491;
    axe[2]=2;
    axe[3]=5;
    jsonCreated();
    serialPuts(fd,out);
}

void axeLoad2(){//放置位置绿中
    axe[0]=511;
    axe[1]=491;
    axe[2]=2;
    axe[3]=5;
    jsonCreated();
    serialPuts(fd,out);
}

void axeLoad3(){//放置位置蓝左
    axe[0]=408;
    axe[1]=491;
    axe[2]=2;
    axe[3]=5;
    jsonCreated();
    serialPuts(fd,out);
}

void axeLoadtoGroundRed() {//放置地面红
    axe[0] = 728;
    axe[1] = 280;
    axe[2] = 391;
    axe[3] = 191;
    jsonCreated();
    serialPuts(fd, out);
}

void axeLoadtoGroundGreen(){//放置地面绿
    axe[0]=875;
    axe[1]=280;
    axe[2]=391;
    axe[3]=191;
    jsonCreated();
    serialPuts(fd,out);
}

void axeLoadtoGroundBlue(){//放置地面蓝
    axe[0]=996;
    axe[1]=280;
    axe[2]=391;
    axe[3]=191;

}

void axeCatch(){//抓取动作
    axe[4]=980;
    jsonCreated();
    serialPuts(fd,out);
}

void axePut(){//放置动作
    axe[4]=880;
    jsonCreated();
    serialPuts(fd,out);
}

void qrcodeAndColorIdentify(){

}

void axeMoveStepRed() {//抓取动作步骤红
    axeInit();
    axeWaitRed();
    axeCatchSpaceRed();
    usleep(1000);//单位为微秒 （百万分之一秒）
    axeCatch();
}

void axePutStepRed(){//放置物块至小车动作步骤红
    axeWaitRed();
    axeLoad1();
    usleep(1000);
    axePut();
}

void axePuttoGroundRed(){//放置物块至固定位置红
    axeInit();
    axeLoad1();
    axeCatch();
    usleep(100);
    axeLoadtoGroundRed();
    axePut();
}

void axeMoveStepGreen(){//抓取动作步骤绿
    axeInit();
    axeWaitGreen();
    axeCatchSpaceGreen();
    usleep(1000);
    axeCatch();
}

void axePutStepGreen(){//放置物块至小车动作步骤绿
    axeLoad2();
    usleep(1000);
    axePut();
}

void axePuttoGroundGreen(){//放置物块至固定位置绿
    axeInit();
    axeLoad2();
    axeCatch();
    usleep(100);
    axeLoadtoGroundGreen();
    axePut();
}

void axeMoveStepBlue(){//抓取动作步骤蓝
    axeInit();
    axeWaitBlue();
    axeCatchSpaceBlue();
    usleep(1000);
    axeCatch();
}

void axePutStepBlue(){//放置物块至小车动作步骤蓝
    axeLoad3();
    axePut();
}

void axePuttoGroundBlue(){//放置物块至固定位置蓝
    axeInit();
    axeLoad3();
    axeCatch();
    usleep(100);
    axeLoadtoGroundBlue();
    axePut();
}

void jsonCreated() {
    json root;
    root = {
            {"bot", {
                            {"movemode", movemode},
                               {"throttle", throttle},
                                  {"direction", direction}
                    }
            },
            {"axe", {0, 0, 0, 0, 0, 0, 0}}
    };
    std::string output = root.dump();
    output = output + "/0";
    out = (char *) output.c_str();
    root.clear();
}

//从起点出发，到达二维码扫描处,停止
void moveStep1(){
    initMode();
    initSpeed();
    changeWaytoDrive();
    axeInit();
    jsonCreated();
    serialPuts(fd,out);
    usleep();//走出起点方块格所用时间

    initMode();
    initSpeed();
    waytoDrive();
    axeInit();
    jsonCreated();
    serialPuts(fd,out);
    usleep();//

    stopMove();
    jsonCreated();
    serialPuts(fd,out);
    usleep();//
}

//行进至物料抓取处，停止(通过调节延时函数，确定行进距离）
void moveStep2(){
    initMode();
    initSpeed();
    waytoDrive();
    axeInit();
    jsonCreated();
    serialPuts(fd,out);
    usleep();//

    stopMove();
    jsonCreated();
    serialPuts(fd,out);
    usleep();//

    axeMoveStepRed();
    axePutStepRed();
    axeMoveStepBlue();
    axePutStepBlue();
    axeMoveStepGreen();
    axePutStepGreen();
}

//右行 前进 停下 放置
void moveStep3(){
    initMode();
    initSpeed();
    changeWaytoDrive();
    axeInit();
    jsonCreated();
    serialPuts(fd,out);
    usleep();

    initMode();
    initSpeed();
    waytoDrive();
    axeInit();
    jsonCreated();
    serialPuts(fd,out);
    usleep();

    modeChange();
    changeSpeed();
    rotatetoDirection();
    axeInit();
    jsonCreated();
    serialPuts(fd,out);
    usleep(1270000);//原地转动方向

    axePuttoGroundRed();
    axePuttoGroundBlue();
    axePuttoGroundGreen();


}

void movestep4(){
    initMode();
    initSpeed();
    changeWaytoDrive();
    axeInit();
    jsonCreated();
    serialPuts(fd,out);
    usleep();

    initMode();
    initSpeed();
    waytoDrive();
    axeInit();
    jsonCreated();
    serialPuts(fd,out);
    usleep();

    modeChange();
    changeSpeed();
    rotatetoDirection();
    axeInit();
    jsonCreated();
    serialPuts(fd,out);
    usleep(1270000);//原地转动方向

}


int main() {
    int i;
    int ret;

    if ( (fd = serialOpen("/dev/ttySn",115200 )) == -1) {//根据argc的值判断是否进行串口的通信
        printf("Usage:/dev/ttySn open error \n");
        return -1;
    }

    moveStep1();
    moveStep2();
    moveStep3();
    movestep4();

    serialClose(fd);
    return 0;
}