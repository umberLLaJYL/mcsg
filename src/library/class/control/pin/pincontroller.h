#ifndef _PINCONTROLLER_H
#define _PINCONTROLLER_H

#include <vector>
#include <map>

#include "pin.h"
#include "../controller.h"

class GPIODirectionController : public _StatusController {
private:
    std::string _directoryTemplate;
    std::map<int, std::pair<int, std::string>> table;

    std::string &_setDirectory(const int idx) {
        return this->_directoryTemplate.replace(20, this->_directoryTemplate.find_last_of("/")-20, std::to_string(idx));
    }

    bool _isExported(const int idx) {
        return this->table.find(idx) != this->table.end();
    }

    bool _setDirection(const int idx, const std::string &direction) {
        if(!this->_isExported(idx))
            return false;
        return !(write((this->table.find(idx)->second.first), direction.c_str(), WriteLen) < 0);
    }

    const std::string &_getDirection(const int idx) {
        std::ifstream fileDirection(this->_setDirectory(idx));
        fileDirection >> this->table.find(idx)->second.second;
        return this->table.find(idx)->second.second;
    }

public:
    GPIODirectionController() : _directoryTemplate(GPIODirection) {
        
    }
    ~GPIODirectionController() {
        for(auto element : this->table)
            close(element.second.first);
    }

    bool insert(const int idx) {
        return this->table.insert({idx, {open(this->_setDirectory(idx).c_str(), O_WRONLY), "out"}}).second;
    }

    bool remove(const int idx) {
        return this->table.erase(idx) == 1;
    }

    bool setDirection(const int idx, const std::string &direction) {
        return this->_setDirection(idx, direction);
    }

    const std::string &getDirection(const int idx) {
        return this->_getDirection(idx);
    }
};

class _Executor {
private:
    std::vector<GPIO> GPIOList;

public:
    _Executor(/* args */) { }
    ~_Executor() { }

    bool pase(const std::string cmd) {

    }

    bool execute(const std::string cmd) {

    }
};

class GPIOController : public _HardwareController {
private:
    std::string identification;
    _Executor executor;

public:
    GPIOController() = default;
    ~GPIOController();

    bool registerController(const std::string &id) {

    }
    bool deregisterController(const std::string &id) {

    }

    bool execute(const std::string &cmd) override {
        this->executor.pase(cmd);
    }
};

#endif
