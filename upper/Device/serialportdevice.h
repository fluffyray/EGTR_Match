//
// Created by Ray on 2020/11/25.
//

#ifndef EGTR_MATCH_UPPER_SERIALPORTDEVICE_H
#define EGTR_MATCH_UPPER_SERIALPORTDEVICE_H
#include <vector>

/*
 * @brief 所有使用串口的设备（抽象的）的基类
 */
class SerialPortDevice{
public:
    SerialPortDevice()=default;
    virtual ~SerialPortDevice()=default;

protected:
    /*
     * @brief 串口传输函数
     * @parm data 用于传输的数据
     */
    void SerialPortDataTransmit(std::vector<unsigned char> data);

private:

};

#endif //EGTR_MATCH_UPPER_SERIALPORTDEVICE_H
