#if !defined(_GPIO_)
#define _GPIO_

#include "GPIOExporter.h"
#include "../../IResource.h"

class GPIO : public Resource {
private:
    const int index;
    static GPIOExporter exporter;

public:
    GPIO(const int idx) : index(idx) {
        this->exporter.exportGPIO(idx);
    }
    ~GPIO() {
        this->exporter.unexportGPIO(this->index);
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
