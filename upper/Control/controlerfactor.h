//
// Created by Ray on 2020/11/25.
//

#ifndef EGTR_MATCH_UPPER_CONTROLERFACTOR_H
#define EGTR_MATCH_UPPER_CONTROLERFACTOR_H

#include <string>
#include <map>

class IControlor;

class ControlerFactory{
public:
    typedef IControlor* (*ControlerConstructFunc)();
    typedef std::map<std::string, ControlerConstructFunc> ControlerMap;
    static void registerControler(std::string controlerName,ControlerConstructFunc fp);
    static void Contorler
protected:

    ControlerFactory() = default;
};


#endif //EGTR_MATCH_UPPER_CONTROLERFACTOR_H
