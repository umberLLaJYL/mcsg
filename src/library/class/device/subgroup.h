#ifndef _SUBGROUP_H
#define _SUBGROUP_H

#include "../control/control.h"

class Subgroup {
private:
    unsigned int size;
    std::map<std::string, Control> group;

public:
    Subgroup(std::string dir) {

    }
    ~Subgroup() {

    }

    unsigned int getSize() {
        return this->size;
    }
};

#endif
