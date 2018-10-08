#ifndef _DEVICE_H
#define _DEVICE_H

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#include "../gpio/gpio.h"
#include "../mpcontrol/control.h"

/**
 * Abstract base class: Device.
 */
class Device {

private:
    std::size_t countAbnormality;
    std::size_t runtime;

    std::string information;
    std::string status;

    std::map<std::string, GPIO> pin;
    std::map<std::string, IoControl> ioControlGroup;
    
public:
    Device() = default;
    Device(const string &conf);
    ~Device();

    // const string &getInformation() const;
    // const string &getStatus() const;

    bool isChange() const;

    virtual void start() = 0;

protected:
    void pinInitialize();

    virtual void operate() = 0;
    virtual void analyse() = 0;

};
class Device;

#endif
