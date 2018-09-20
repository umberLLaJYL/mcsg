#ifndef _CONTROL_H
#define _CONTROL_H

#include <map>
#include <vector>
#include <iostream>

#include "../gpio/gpio.h"

class IoControl {
private:
    double status:

    std::vector<GPIO> pin;
    std::map<std::string, std::string> sequence;

public:
    IoControl(const std::string &);
    ~IoControl();

    bool operator == (double);
    bool operator != (double);
    bool operator [] (double);

    bool execute(const std::string &);

    double getStatus();
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
