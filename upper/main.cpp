//
// Created by peng chen on 2020/12/19.
//

#include <iostream>
#include <cstring>
#include "cserial.h"
#include <cstdio>
#include <cstdlib>
#include "json.hpp"
#include <unistd.h>

using json = nlohmann::json;
using namespace std;

int throttle=0;//油门量，初始速度为0
int direction= 270;//方向，初始方向为正前方
string movemode = "translation";//移动模式，初始为平动
int axe[5] = {37,513,409,425,880};//舵机移动角度，初始为静止状态
char *out=NULL;//json文件字符，初始为空
int fd = FALSE;

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
    throttle=60;
    //printf("%f",throttle);
}

void changeSpeed(){//改变初始速度与转动速度
    if(movemode=="translation"){
        throttle=60;
    }
    else if(movemode=="rotate"){
        throttle=15;
    }

    //printf("%f",throttle);
}

void stopMove(){//停下小车
    throttle=0;
}

void waytoDrive(){//初始化前进方向
    direction= 270;
    //printf("%f",direction);
}

void changeWaytoDrive(){//改变前进方向
    if(movemode=="translation"){
        if(direction>=0)
        direction=direction;
        else
            direction=direction+360;
    }
    else if(movemode=="rotate"){
        direction=(direction-90)%360;
    }
    //printf("%f",direction);
}

void initMode(){//初始化移动模式
    movemode="translation";
    //printf("%s",movemode.c_str());
}

void modeChange(){//改变移动模式方法
    if(movemode=="translation"){
        movemode="rotate";
    }
    else if(movemode=="rotate"){
        movemode="translation";
    }
    //printf("%s",movemode.c_str());
}

void axeInit(){//初始化
    axe[0]=37;
    axe[1]=513;
    axe[2]=409;
    axe[3]=425;
    axe[4]=880;
}

void axeCatchSpace(){//抓取位置
    axe[0]=270;
    axe[1]=513;
    axe[2]=409;
    axe[3]=425;
}

void axeLoad1(){//放置位置1
    axe[0]=620;
    axe[1]=491;
    axe[2]=2;
    axe[3]=5;
}

void axeLoad2(){//放置位置2
    axe[0]=511;
    axe[1]=491;
    axe[2]=2;
    axe[3]=5;
}

void axeLoad3(){//放置位置3
    axe[0]=408;
    axe[1]=491;
    axe[2]=2;
    axe[3]=5;
}

void axeCatch(){//抓取动作
    axe[4]=980;
}

void axePut(){//放置动作
    axe[4]=880;
}

void qrcodeAndColorIdentify(){

}

void axeMoveStep1(){//抓取动作步骤1
    axeCatchSpace();
    jsonCreated();
    //    UART_Send(fd,out,strlen(out));
    usleep(1000);
    axeCatch();
    jsonCreated();
    //    UART_Send(fd,out,strlen(out));
}

void axePutStep1(){//放置物块至小车动作步骤1
    axeLoad1();
    jsonCreated();
    //    UART_Send(fd,out,strlen(out));
    usleep(1000);
    axePut();
    jsonCreated();
    //    UART_Send(fd,out,strlen(out));
}

void axePutStep2(){//放置物块至小车动作步骤2
    axeLoad2();
    jsonCreated();
    //    UART_Send(fd,out,strlen(out));
    usleep(1000);
    axePut();
    jsonCreated();
    //    UART_Send(fd,out,strlen(out));
}

void axePutStep3(){//放置物块至小车动作步骤3
    axeLoad3();
    jsonCreated();
    //    UART_Send(fd,out,strlen(out));
    usleep(1000);
    axePut();
    jsonCreated();
    //    UART_Send(fd,out,strlen(out));
}

void axePutToTarget(){//

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
    out = (char *) output.c_str();
    root.clear();
}

//从起点出发，到达二维码扫描处,停止
void moveStep1(){
    initMode();
    initSpeed();
    waytoDrive();
    axeInit();
    jsonCreated();
    printf("%s\n",out);
//    UART_Send(fd,out,strlen(out));
    //sleep(1000);//延时函数，时间为？ms
    //stopMove();
    //jsonCreated();
    //printf("%s\n",out);
//    UART_Send(fd,out,strlen(out));
    //usleep(1000);//延时函数，时间为？ms
}

//行进至物料抓取处，停止(通过调节延时函数，确定行进距离）
void moveStep2(){
    initMode();
    initSpeed();
    waytoDrive();
    axeInit();
    jsonCreated();
    printf("%s\n",out);
//    UART_Send(fd,out,strlen(out));
    //sleep(1000);//延时函数，时间为？ms

    //stopMove();
    //jsonCreated();
    //printf("%s\n",out);
//    UART_Send(fd,out,strlen(out));
    //usleep(1000);//延时函数，时间为？ms
}

//前行 转弯 前行 停下
void moveStep3(){
    initMode();
    initSpeed();
    waytoDrive();
    axeInit();
    jsonCreated();
    printf("%s\n",out);
//    UART_Send(fd,out,strlen(out));
    usleep(1000);//延时函数，时间为？ms

    modeChange();
    changeSpeed();
    changeWaytoDrive();
    axeInit();
    jsonCreated();
    printf("%s\n",out);
//    UART_Send(fd,out,strlen(out));
    usleep(1000);//延时函数，时间为？ms
}


int main(int argc,char** argv) {
    int i;
    char rcv_buf[512];//接收字符集，
    int ret;

   if (argc != 2) {//根据argc的值判断是否进行串口的通信
       printf("Usage:/dev/ttySn \n");
       return FALSE;
   }
   fd = UART_Open(fd, argv[1]);//判断端口是否开启
   if (FALSE == fd) {
       printf("open error\n");
       exit(1);
   }
   ret = UART_Init(fd, 9600, 0, 8, 1, 'N');
   if (FALSE == fd) {
       printf("Set Port Error\n");
       exit(1);
   }
    moveStep1();
    moveStep2();

   memset(rcv_buf, 0, sizeof(rcv_buf));
   for (i = 0;; i++) {
       ret = UART_Recv(fd, rcv_buf, 512);

       if (ret > 0) {
           rcv_buf[ret] = '\0';
           printf("%s", rcv_buf);
       } else {
           printf("cannot receive data1\n");
           break;
       }
       if ('\n' == rcv_buf[ret - 1])
           break;
   }
   UART_Close(fd);
    return 0;
}