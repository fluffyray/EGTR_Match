//
// Created by Ray on 2020/11/25.
//

#ifndef EGTR_MATCH_UPPER_SERIALPORTDEVICE_H
#define EGTR_MATCH_UPPER_SERIALPORTDEVICE_H
#include <vector>

class SerialPortDevice{
public:
    SerialPortDevice()=default;
    virtual ~SerialPortDevice()=default;

protected:
    void SerialPortDataTransmit(std::vector<unsigned char> data);

private:

};

#endif //EGTR_MATCH_UPPER_SERIALPORTDEVICE_H
