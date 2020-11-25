//
// Created by Ray on 2020/11/25.
//

#include "controlerfactor.h"

ControlerFactory::ControlerMap* getControlerConstructFuncMap(){
    static ControlerFactory::ControlerMap* controlerMap = new ControlerFactory::ControlerMap;
    return controlerMap;
}

void ControlerFactory::registerControler(std::string controlerName, ControlerConstructFunc fp) {
    ControlerFactory::ControlerMap* controlerMap = getControlerConstructFuncMap();
    if (nullptr == fp) {
        return;
    }
    if (controlerMap->find(controlerName) != controlerMap->end()) {
        return;
    }
    controlerMap->insert(ControlerFactory::ControlerMap::value_type(controlerName,fp));
}