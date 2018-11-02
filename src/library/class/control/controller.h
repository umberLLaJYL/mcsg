#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "pin/pin.h"
#include "adc/adc.h"
#include "dac/dac.h"
#include "serial/serial.h"
#include "../../json/rapidjson/document.h"

class _HardwareController {
private:

public:
    _HardwareController() {

    }
    ~_HardwareController() {

    }

    virtual bool execute(const std::string &) = 0;
};


class _ControllerRegister {
private:
    /* data */
public:
    _ControllerRegister(/* args */) { }
    ~_ControllerRegister() { }
};


class _StatusController {
private:

protected:

public:
    _StatusController(/* args */) { }
    ~_StatusController() { }

};

class Initializer {
private:
    /* data */
public:
    Initializer() { }
    ~Initializer() { }
};

class SeqConverter {
private:
    /* data */
public:
    SeqConverter() { }
    ~SeqConverter() { }
};

class Control {
private:
    std::string identification;
    // std::map<std::string, > sequence;

protected:
    bool valid;

public:
    Control() {

    }
    ~Control() {

    }

    virtual bool execute(const std::string &order) = 0;

    bool isValid() const {
        return this->valid;
    }

    virtual int getParameter(const std::string &parm) = 0;

    std::string &getIdentification() {
        return this->identification;
    }
};

// class Control {
// private:

//     bool _initialize(const std::string &file) {
//         std::ifstream fileConfig(file);
//         std::string line;
//         std::string option;
//         rapidjson::Document ioCtrl;

//         this->identification = file;
//         this->valid = false;
//         this->pinNum = 0;

//         if(!fileConfig.is_open())
//             return false;

//         while(std::getline(fileConfig, line))
//             option += line;
//         fileConfig.close();

//         ioCtrl.Parse(option.c_str());

//         this->valid = true;
//         this->_updata();
//     }

//     void _deinitialize() {
//         this->pinNum = 0;
//         this->pin.clear();
//         this->sequence.clear();
//         this->parameter.clear();
//     }

//     void _updata() {
//         for(auto &element : this->parameter) {
//             element.second.second = 0;
//             for(int pinSelect = 0; pinSelect != this->pinNum; ++pinSelect)
//                 if(element.second.first & (0x01 << pinSelect))
//                     element.second.second |= (this->pin[pinSelect].getValue() << pinSelect);
//         }
//     }

//     bool _execute(const std::string &order) {
//         std::map<std::string, std::vector<int>>::iterator element = this->sequence.find(order);
//         if(element == this->sequence.end())
//             return false;

//         switch(element->second.size()) {
//             case 1: {
//                 for(int pinSelect = 0; pinSelect != this->pinNum; ++pinSelect)
//                     this->pin[pinSelect].setValue(element->second[0] & (0x01 << pinSelect));
//                 break;
//             }

//             case 3: {
//                 for(int pinSelect = 0; pinSelect != this->pinNum; ++pinSelect) {
//                     if(element->second[0] & (0x01 << pinSelect)) {
//                         if(element->second[1] & (0x01 << pinSelect))
//                             this->pin[pinSelect].setDirection("out");
//                         else
//                             this->pin[pinSelect].setDirection("in");
//                         this->pin[pinSelect].setValue(element->second[2] & (0x01 << pinSelect));
//                     }
//                 }
//                 break;
//             }

//             default: break;
//         }    
//         this->_updata();
//         return true;
//     }

//     bool _setPinDirection(int pinIdx, const char *dir) {
//         if((pinIdx < 1) || (pinIdx > this->pinNum))
//             return false;
//         return this->pin[pinIdx-1].setDirection(dir);
//     }

//     bool _setPinValue(int pinIdx, int vlu) {
//         if((pinIdx < 1) || (pinIdx > this->pinNum))
//             return false;
//         return this->pin[pinIdx-1].setValue(vlu);
//     }

//     int _getParameter(const std::string &parm) {
//         std::map<std::string, std::pair<int, int>>::iterator element = this->parameter.find(parm);
//         if(element == this->parameter.end())
//             return 0xff;
//         return element->second.second;
//     }

//     int _getPinValue(int pinIdx) {
//         if((pinIdx < 1) || (pinIdx > this->pinNum))
//             return -1;
//         return this->pin[pinIdx-1].getValue();
//     }

// public:
//     Control(const std::string &prefix) : valid(false), pinNum(0), identification(prefix) {
//         this->_initialize(prefix);
//     }

//     ~Control() {
//         this->_deinitialize();
//     }

//     int operator [] (const std::string parm) {
//         return this->getParameter(parm);
//     }

//     void reinitialize(const std::string &prefix) {
//         this->_deinitialize();
//         this->_initialize(prefix);
//     }

//     void deinitialize() {
//         this->_deinitialize();
//     }

//     void updata() {
//         this->_updata();
//     }

//     bool execute(const std::string &order) {
//         return this->_execute(order);
//     }

//     bool isValid() const {
//         return this->valid;
//     }

//     bool setPinDirection(int pinIdx, const char *dir) {
//         return this->_setPinDirection(pinIdx, dir);
//     }

//     bool setPinValue(int pinIdx, int vlu) {
//         return this->_setPinValue(pinIdx, vlu);
//     }

//     int getParameter(const std::string &parm) {
//         return this->_getParameter(parm);
//     }

//     int getPinValue(int pinIdx) {
//         return this->_getPinValue(pinIdx);
//     }
// };

#endif
