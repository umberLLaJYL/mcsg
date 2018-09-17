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

bool GPIO::_setGPIO(_FD fd, const char *option)
{
    if(write(fd, option, 8) < 0)
        return false;
    return true;
}

bool GPIO::_getOption(_FD fd)
{
    memset(this->_option, 0, 8);
    if(read(fd, this->_option, 8) < 0)
        return false;
    return true;
}

bool GPIO::_setDirection(const int dir)
{
    if(dir)
        return this->_setGPIO(_w_gpioDirection, "out");
    return this->_setGPIO(_w_gpioDirection, "in");
}

bool GPIO::_setValue(const int vlu)
{
    if(_direction != 0)
        return false;
    if(vlu)
        return this->_setGPIO(_gpioValue, "1");
    return this->_setGPIO(_gpioValue, "0");
}

bool GPIO::_setEdge(const char *edge)
{
    if(_direction != 0)
        return false;
    return this->_setGPIO(_gpioEdge, edge);
}

GPIO::GPIO(const unsigned int idx) : index(idx), _direction(0)
{
    char idxStr[8];
    std::string dir("/sys/class/gpio/gpio");

    this->_exportGPIO(idx);

    snprintf(idxStr, sizeof(idxStr), "%d", idx);
    dir += idxStr;

    _r_gpioDirection = open((dir+"/direction").c_str(), O_RDONLY);
    _w_gpioDirection = open((dir+"/direction").c_str(), O_WRONLY);
    _gpioValue = open((dir+"/value").c_str(), O_WRONLY);
    _gpioEdge = open((dir+"/edge").c_str(), O_WRONLY);
}

GPIO::~GPIO()
{
    close(_w_gpioDirection);
    close(_r_gpioDirection);
    close(_gpioValue);
    close(_gpioEdge);

    this->_unexportGPIO(index);
}

GPIO &GPIO::operator = (int vlu)
{
    _setValue(vlu);
    return *this;
}

bool GPIO::output()
{
    return this->_setDirection(1);
}
bool GPIO::input()
{
    return this->_setDirection(0);
}

bool GPIO::pullUp()
{
    return this->_setValue(1);
}
bool GPIO::pullDown()
{
    return this->_setValue(0);
}

int GPIO::getValue() const
{
    return this->_value;
}
int GPIO::getDirection() const
{
    return this->_direction;
}

bool GPIO::irqNone()
{
    return this->_setEdge("none");
}
bool GPIO::irqRising()
{
    return this->_setEdge("rising");
}
bool GPIO::irqFalling()
{
    return this->_setEdge("falling");
}
bool GPIO::irqBoth()
{
    return this->_setEdge("both");
}

#endif
