#ifndef _CONTROL_H
#define _CONTROL_H

#include <map>

class Action {
private:
    
public:
    Action();
    ~Action();
};

class Control {
private:
    std::map<> pin;

public:
    Control();
    ~Control();

};

#include "control.cpp"

#endif