#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>
#include<errno.h>
#include<string.h>


#define FALSE -1
#define TRUE 0

/*****************************************************************
* 名称： UART0_Open
* 功能： 打开串口并返回串口设备文件描述
* 入口参数： fd :文件描述符 port :串口号(ttyS0,ttyS1,ttyS2)
* 出口参数： 正确返回为1，错误返回为0
*****************************************************************/
int UART_Open(int fd,char* port);

void UART_Close(int fd);

/*******************************************************************
* 名称： UART0_Set
* 功能： 设置串口数据位，停止位和效验位
* 入口参数： fd 串口文件描述符
* speed 串口速度
* flow_ctrl 数据流控制
* databits 数据位 取值为 7 或者8
* stopbits 停止位 取值为 1 或者2
* parity 效验类型 取值为N,E,O,,S
*出口参数： 正确返回为1，错误返回为0
*******************************************************************/
int UART_Set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity);


int UART_Init(int fd, int speed,int flow_ctrlint ,int databits,int stopbits,char parity);

/*******************************************************************
* 名称： UART0_Recv
* 功能： 接收串口数据
* 入口参数： fd :文件描述符
* rcv_buf :接收串口中数据存入rcv_buf缓冲区中
* data_len :一帧数据的长度
* 出口参数： 正确返回为1，错误返回为0
*******************************************************************/
int UART_Recv(int fd, char *rcv_buf,int data_len);

/*******************************************************************
* 名称： UART0_Send
* 功能： 发送数据
* 入口参数： fd :文件描述符
* send_buf :存放串口发送数据
* data_len :一帧数据的个数
* 出口参数： 正确返回为1，错误返回为0
*******************************************************************/
int UART_Send(int fd, char *send_buf,int data_len);