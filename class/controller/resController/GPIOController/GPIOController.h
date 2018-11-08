#ifndef _PINCONTROLLER_H
#define _PINCONTROLLER_H

#include <vector>
#include <map>

#include "../ResourceController.h"
#include "../opController/GPIODirectionController/GPIODirectionController.h"
#include "GPIOExporter.h"

class GPIOController : public ResourceController {
private:
    static const int registerFile;
    static GPIODirectionController directionController;
    // static GPIODValueController valueController;
    // static GPIOIrqController irqController;
    static GPIOExporter exporter;

public:
    GPIOController() = default;
    ~GPIOController();

    bool execute(const std::string &cmd) override {

    }

    bool exportGPIO(const int idx) {
        return this->exporter.exportGPIO(idx);
    }

    bool unexportGPIO(const int idx) {
        return this->exporter.unexportGPIO(idx);
    }

    bool setDirection(const int idx, const std::string &direction) {
        return this->directionController.setDirection(idx, direction);
    }
};

GPIOController gpioController;

#endif
