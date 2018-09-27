#ifndef _CONTROL_H
#define _CONTROL_H

#include <map>
#include <vector>
#include <iostream>

#include "../gpio/gpio.h"
#include "../../json/rapidjson/document.h"

class IoControl {
private:
    int pinAct;
    int pinStat;

    std::vector<GPIO> pin;
    std::map<std::string, int> sequence;

public:
    IoControl(const std::string &);
    ~IoControl();
    
    // bool operator == (int);
    // bool operator != (int);
    // bool operator [] (int);

    bool execute(const std::string &);

    int getStatus();
    int getStatus(std::size_t);
};

class AdControl {
private:
    /* data */
public:
    AdControl(/* args */) { }
    ~AdControl() { }
};

class DaControl {
private:
    /* data */
public:
    DaControl(/* args */) { }
    ~DaControl() { }
};

class SerialControl {
private:
    /* data */
public:
    SerialControl(/* args */) { }
    ~SerialControl() { }
};

#include "iocontrol.cpp"

#endif
