#ifndef _GPIO_H
#define _GPIO_H

#include <unistd.h>
#include <fcntl.h>

#include <string>

class GPIO {
private:
    static const int _export;
    static const int _unexport;

    int _gpioDirection;
    int _gpioValue;
    int _gpioEdge;

    int index;
    
    static bool _register(const int, const int);

    static bool _exportGPIO(const int);
    static bool _unexportGPIO(const int);

    bool _setGPIO(int, const std::string &);

    bool _getOption(const std::string &, std::string &);

public:
    GPIO(const int);
    GPIO(const int, const std::string &);
    GPIO(const int, const int);
    ~GPIO();

    GPIO &operator = (const int);
    bool operator == (const int);
    bool operator != (const int);

    void reexport(const int);
    void reexport(const int, const std::string &);
    void reexport(const int, const int);
    void unexport();

    bool output();
    bool input();

    bool pullUp();
    bool pullDown();

    int getIndex() const;
    int getValue();
    int getDirection();

    bool irqNone();
    bool irqRising();
    bool irqFalling();
    bool irqBoth();
};

#include "gpio.cpp"

#endif
