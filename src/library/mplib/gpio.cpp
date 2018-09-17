#ifndef _GPIO_CPP_
#define _GPIO_CPP_

#include <unistd.h>
#include <string.h>

#include "mplib.h"

const int GPIO::_export = open("/sys/class/gpio/export", O_WRONLY);
const int GPIO::_unexport = open("/sys/class/gpio/unexport", O_WRONLY);

bool GPIO::_register(const _FD _un_export, const int idx)
{
    char _index[8];

    snprintf(_index, sizeof(_index), "%d", idx);
    if(write(_un_export, _index, 8) < 0)
        return false;
    return true;
}

bool GPIO::_exportGPIO(const int idx)
{
    return GPIO::_register(_export, idx);
}
bool GPIO::_unexportGPIO(const int idx)
{
    return GPIO::_register(_unexport, idx);
}

bool GPIO::_setGPIO(_FD fd, const std::string &option)
{
    if(write(fd, option.c_str(), 8) < 0)
        return false;
    return true;
}

bool GPIO::_getOption(const std::string &key, std::string &value)
{
    _FD fd;
    char idxStr[8], option[16] = {0};
    std::string dir("/sys/class/gpio/gpio");

    snprintf(idxStr, sizeof(idxStr), "%d/", this->index);
    dir += idxStr;
    dir += key;

    if((fd = open(dir.c_str(), O_RDONLY)) < 0)
        return false;
    if(read(fd, option, sizeof(option)) < 0)
        return false;
    close(fd);
    
    value.assign(option);
    return true;
}

GPIO::GPIO(const int idx) : index(idx)
{
    char idxStr[8];
    std::string dir("/sys/class/gpio/gpio");

    this->_exportGPIO(idx);

    snprintf(idxStr, sizeof(idxStr), "%d", idx);
    dir += idxStr;

    _gpioDirection = open((dir+"/direction").c_str(), O_WRONLY);
    _gpioValue = open((dir+"/value").c_str(), O_WRONLY);
    _gpioEdge = open((dir+"/edge").c_str(), O_WRONLY);
}

GPIO::GPIO(const int idx, const std::string& direction) : index(idx)
{
    char idxStr[8];
    std::string dir("/sys/class/gpio/gpio");

    this->_exportGPIO(idx);

    snprintf(idxStr, sizeof(idxStr), "%d", idx);
    dir += idxStr;

    _gpioDirection = open((dir+"/direction").c_str(), O_WRONLY);
    _gpioValue = open((dir+"/value").c_str(), O_WRONLY);
    _gpioEdge = open((dir+"/edge").c_str(), O_WRONLY);
}

GPIO::~GPIO()
{
    close(_gpioDirection);
    close(_gpioValue);
    close(_gpioEdge);
    this->_unexportGPIO(index);
}

GPIO &GPIO::operator = (const int vlu)
{
    if(vlu)
        this->_setGPIO(_gpioValue, "1");
    this->_setGPIO(_gpioValue, "0");
    return *this;
}

bool GPIO::operator == (const int vlu)
{
    
}

bool GPIO::operator != (const int vlu)
{

}

bool GPIO::output()
{
    return this->_setGPIO(_gpioDirection, "out");
}
bool GPIO::input()
{
    return this->_setGPIO(_gpioDirection, "in");
}

bool GPIO::pullUp()
{
    return this->_setGPIO(_gpioValue, "1");
}
bool GPIO::pullDown()
{
    return this->_setGPIO(_gpioValue, "0");
}

int GPIO::getIndex() const
{
    return this->index;
}

int GPIO::getValue()
{
    std::string value;

    if(this->_getOption("value", value) == false)
        return -1;
    if(value == "1\n")
        return 1;
    else if(value == "0\n")
        return 0;
    else
        return -1;
}
int GPIO::getDirection()
{
    std::string direction;

    if(this->_getOption("direction", direction) == false)
        return -1;
    if(direction == "out\n")
        return 1;
    else if(direction == "in\n")
        return 0;
    else
        return -1;
}

bool GPIO::irqNone()
{
    return this->_setGPIO(_gpioEdge, "none");
}
bool GPIO::irqRising()
{
    return this->_setGPIO(_gpioEdge, "rising");
}
bool GPIO::irqFalling()
{
    return this->_setGPIO(_gpioEdge, "falling");
}
bool GPIO::irqBoth()
{
    return this->_setGPIO(_gpioEdge, "both");
}

#endif
