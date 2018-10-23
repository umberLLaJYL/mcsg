#ifndef _PIN_H
#define _PIN_H

#include <map>

#include "gpio/gpio.h"

class Pin {
private:
    std::map<std::string, GPIO> pin;

public:
    Pin(unsigned int idx) {

    }
    ~Pin() {

    }
};

#endif
