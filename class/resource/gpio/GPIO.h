#ifndef _PIN_H
#define _PIN_H

#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <set>

class GPIO {
private:
    const int index;
    static GPIOController &_gpioController;

public:
    GPIO(const int idx) : index(idx) {
        exporter.exportGPIO(idx);
    }
    ~GPIO() {
        exporter.unexportGPIO(this->index);
    }

    template<class Controller>
    Controller &bind() {

    }

    bool output() {
        return this->directionOperator.setDirection("out");
    }
    bool input() {
        return this->directionOperator.setDirection("in");
    }
    bool setDirection(const char *direction) {
        return this->directionOperator.setDirection(direction);
    }

    bool pullUp() {

    }
    bool pullDown() {

    }
    bool setValue(const char *value) {

    }

    bool irqNone();
    bool irqRising();
    bool irqFalling();
    bool irqBoth();
    bool setIrq(const char *irq) {

    }

    int getValue() {

    }

    const std::string &getDirection() {
        return this->directionOperator.getDirection();
    }

    const std::string &getIrq() {
        
    }

    GPIO &bind(GPIODirectionOperator &gdc) {
        this->directionOperator = gdc;
        return *this;
    }
};

#endif
