#ifndef _PIN_H
#define _PIN_H

#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <set>

#define WriteLen 8
#define GPIODir "/sys/class/gpio/gpio"
#define GPIODirection "/sys/class/gpio/gpiox/direction"
#define GPIOValue "/value"
#define GPIOIrq "/edge"

#define pinAct(action) GPIODir#action

class GPIOExporter {
private:
    static const int fdExport, fdUnexport;
    
public:
    GPIOExporter() {

    }
    ~GPIOExporter() {
        close(this->fdExport);
        close(this->fdUnexport);
    }

    bool exportGPIO(const int idx) {
        return !(write(this->fdExport, std::to_string(idx).c_str(), WriteLen) < 0);
    }

    bool unexportGPIO(const int idx) {
        return !(write(this->fdUnexport, std::to_string(idx).c_str(), WriteLen) < 0);
    }
};

const int GPIOExporter::fdExport = open(pinAct(/export), O_WRONLY);
const int GPIOExporter::fdUnexport = open(pinAct(/unexport), O_WRONLY);

class GPIO {
private:
    const int index;
    static GPIOExporter exporter;
    static GPIODirectionController directionController;
    // static GPIODValueController valueController;
    // static PinIrqController irqController;

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
        return this->directionController.setDirection(this->index, "out");
    }
    bool input() {
        return this->directionController.setDirection(this->index, "in");
    }
    bool setDirection(const char *direction) {
        return this->directionController.setDirection(this->index, direction);
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
        return this->directionController.getDirection(this->index);
    }

    const std::string &getIrq() {
        
    }

    GPIO &bind(PinDirectionController &pdc) {
        this->directionController = pdc;
        return *this;
    }
};

#endif
