#if !defined(_GPIO_)
#define _GPIO_

#include "../Resource.h"
#include "../../controller/resController/GPIOController/GPIOController.h"

class GPIO : public Resource {
private:
    const int index;
    static GPIOController _gpioController;

public:
    GPIO(const int idx) : index(idx) {
        this->_gpioController.exportGPIO(idx);
    }
    ~GPIO() {
        this->_gpioController.unexportGPIO(this->index);
    }

    bool output() {
        return this->_gpioController.setDirection(this->index, "out");
    }
    bool input() {
        return this->_gpioController.setDirection(this->index, "in");
    }
    bool setDirection(const std::string &direction) {
        return this->_gpioController.setDirection(this->index, direction);
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
        return this->_gpioController.getDirection(this->index);
    }

    const std::string &getIrq() {
        
    }
};

#endif // _GPIO_
