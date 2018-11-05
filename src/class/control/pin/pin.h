#ifndef _PIN_H
#define _PIN_H

#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <set>

#define WriteLen 8
#define DirGPIO "/sys/class/gpio/gpio"
#define DirGPIODirection "/sys/class/gpio/gpiox/direction"
#define DirGPIOValue "/value"
#define DirGPIOIrq "/edge"

#define pinAct(action) DirGPIO#action

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
    static GPIODirectionOperator directionOperator;
    const std::string dd;
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
