//
// Created by Ray on 2020/11/25.
//

#ifndef EGTR_MATCH_UPPER_SERIALCOMMUNICATE_H
#define EGTR_MATCH_UPPER_SERIALCOMMUNICATE_H

#include <string>
#include <vector>
class SerialComminicate{
public:
    SerialComminicate(std::string COM,int b);
    void recevie(std::vector<unsigned char>& data);
};

#endif //EGTR_MATCH_UPPER_SERIALCOMMUNICATE_H
