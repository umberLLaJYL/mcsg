#ifndef _PINCONTROLLER_H
#define _PINCONTROLLER_H

#include <vector>
#include <map>

#include "pin.h"
#include "../controller.h"

class GPIODirectionOperator : public Actor {
private:
    int fdDirection;
    std::string _directory;
    std::string _direction;

    std::string &_setDirectory(const int idx) {
        return this->_directoryTemplate.replace(20, this->_directoryTemplate.find_last_of("/")-20, std::to_string(idx));
    }

    bool _isInvalid() {
        return this->fdDirection < 0;
    }

    bool _setDirection(const std::string &direction) {
        if(this->_isInvalid())
            return false;
        return !(write(this->fdDirection, direction.c_str(), WriteLen) < 0);
    }

    const std::string &_getDirection() {
        std::ifstream fileDirection(this->_setDirectory());
        if(!fileDirection.is_open())
            return "error";
        fileDirection >> this->_direction;
        return this->_direction;
    }

public:
    GPIODirectionOperator() {
        this->_directory = this->_setDirectory();
    }
    ~GPIODirectionOperator() {
        close(this->fdDirection);
    }

    bool setDirection(const std::string &direction) {
        return this->_setDirection(direction);
    }

    const std::string &getDirection() {
        return this->_getDirection();
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
