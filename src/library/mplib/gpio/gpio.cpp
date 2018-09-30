#ifndef _GPIO_CPP
#define _GPIO_CPP

#include "gpio.h"

const int GPIO::_export = open("/sys/class/gpio/export", O_WRONLY);
const int GPIO::_unexport = open("/sys/class/gpio/unexport", O_WRONLY);

bool GPIO::_register(const int _un_export, const int idx)
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

bool GPIO::_setGPIO(int fd, const std::string &option)
{
    if(write(fd, option.c_str(), 8) < 0)
        return false;
    return true;
}

bool GPIO::_getOption(const std::string &key, std::string &value)
{
    int fd;
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
    char opt[8];
    std::string dir("/sys/class/gpio/gpio");

    this->_exportGPIO(idx);

    snprintf(opt, sizeof(opt), "%d", idx);
    dir += opt;

    this->_gpioDirection = open((dir+"/direction").c_str(), O_WRONLY);
    this->_gpioValue = open((dir+"/value").c_str(), O_WRONLY);
    this->_gpioEdge = open((dir+"/edge").c_str(), O_WRONLY);
}

GPIO::GPIO(const int idx, const std::string& option) : index(idx)
{
    char opt[8];
    std::string dir("/sys/class/gpio/gpio");

    this->_exportGPIO(idx);

    snprintf(opt, sizeof(opt), "%d", idx);
    dir += opt;

    this->_gpioDirection = open((dir+"/direction").c_str(), O_WRONLY);
    this->_gpioValue = open((dir+"/value").c_str(), O_WRONLY);
    this->_gpioEdge = open((dir+"/edge").c_str(), O_WRONLY);

    if(option == "out")
        write(this->_gpioDirection, "out", 8);
    else {
        write(this->_gpioDirection, "in", 8);
        write(this->_gpioEdge, option.c_str(), 8);        
    }
}

GPIO::GPIO(const int idx, const int vlu) : index(idx)
{
    char opt[8];
    std::string dir("/sys/class/gpio/gpio");

    this->_exportGPIO(idx);

    snprintf(opt, sizeof(opt), "%d", idx);
    dir += opt;

    this->_gpioDirection = open((dir+"/direction").c_str(), O_WRONLY);
    this->_gpioValue = open((dir+"/value").c_str(), O_WRONLY);
    this->_gpioEdge = open((dir+"/edge").c_str(), O_WRONLY);

    write(this->_gpioDirection, "out", 8);
    snprintf(opt, sizeof(opt), "%d", vlu);
    write(this->_gpioValue, opt, 8);
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
    int value;

    if((value = this->getValue()) < 0)
        return false;
    if(value == vlu)
        return true;
    return false;
}

bool GPIO::operator != (const int vlu)
{
    return !GPIO::operator == (vlu);
}

void GPIO::reexport(const int idx)
{
    char opt[8];
    std::string dir("/sys/class/gpio/gpio");

    close(_gpioDirection);
    close(_gpioValue);
    close(_gpioEdge);
    this->_unexportGPIO(this->index);

    this->index = idx;
    this->_exportGPIO(idx);

    snprintf(opt, sizeof(opt), "%d", idx);
    dir += opt;

    this->_gpioDirection = open((dir+"/direction").c_str(), O_WRONLY);
    this->_gpioValue = open((dir+"/value").c_str(), O_WRONLY);
    this->_gpioEdge = open((dir+"/edge").c_str(), O_WRONLY);
}
void GPIO::reexport(const int idx, const std::string &option)
{
    char opt[8];
    std::string dir("/sys/class/gpio/gpio");

    close(_gpioDirection);
    close(_gpioValue);
    close(_gpioEdge);
    this->_unexportGPIO(this->index);

    this->_exportGPIO(idx);

    snprintf(opt, sizeof(opt), "%d", idx);
    dir += opt;

    this->_gpioDirection = open((dir+"/direction").c_str(), O_WRONLY);
    this->_gpioValue = open((dir+"/value").c_str(), O_WRONLY);
    this->_gpioEdge = open((dir+"/edge").c_str(), O_WRONLY);

    if(option == "out")
        write(this->_gpioDirection, option.c_str(), 8);
    else {
        write(this->_gpioDirection, "in", 8);
        write(this->_gpioEdge, option.c_str(), 8);        
    }
}
void GPIO::reexport(const int idx, const int vlu)
{
    char opt[8];
    std::string dir("/sys/class/gpio/gpio");

    close(_gpioDirection);
    close(_gpioValue);
    close(_gpioEdge);
    this->_unexportGPIO(this->index);

    this->_exportGPIO(idx);

    snprintf(opt, sizeof(opt), "%d", idx);
    dir += opt;

    this->_gpioDirection = open((dir+"/direction").c_str(), O_WRONLY);
    this->_gpioValue = open((dir+"/value").c_str(), O_WRONLY);
    this->_gpioEdge = open((dir+"/edge").c_str(), O_WRONLY);

    write(this->_gpioDirection, "out", 8);
    snprintf(opt, sizeof(opt), "%d", vlu);
    write(this->_gpioValue, opt, 8);
}

void GPIO::unexport()
{
    close(_gpioDirection);
    close(_gpioValue);
    close(_gpioEdge);
    this->_unexportGPIO(index);
}

bool GPIO::output()
{
    return this->_setGPIO(_gpioDirection, "out");
}
bool GPIO::input()
{
    return this->_setGPIO(_gpioDirection, "in");
}
bool GPIO::setDirection(const char *dir)
{
    return this->_setGPIO(_gpioDirection, dir);
}

bool GPIO::pullUp()
{
    return this->_setGPIO(_gpioValue, "1");
}
bool GPIO::pullDown()
{
    return this->_setGPIO(_gpioValue, "0");
}
bool GPIO::setValue(int vlu)
{
    if(vlu)
        return this->_setGPIO(_gpioValue, "1");
    else
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
