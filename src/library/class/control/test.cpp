#include <vector>
#include <iostream>
#include <fstream>

#include "pin/pin.h"
#include "adc/adc.h"
#include "dac/dac.h"
#include "serial/serial.h"
#include "../../json/rapidjson/document.h"

using namespace rapidjson;

class Control {
private:
    GPIO gpio;
    
protected:

public:
    Control() {

    }
    ~Control() {

    }

    // virtual bool initialize(const std::string &file) = 0;
    // virtual void deinitialize() = 0;
    virtual bool execute(const std::string &order) = 0;    
    virtual std::string & get() = 0;    
};

class Ctrl : public Control {
public:

    bool execute(const std::string &order) override {
        std::cout << order << std::endl;
    }

    std::string &get() override {
    }
};

class Ctrl1 : public Control {
    std::string s;

public:
    bool execute(const std::string &order) override {
        s = order;
        std::cout << "czdcszdcdccsdcsc" << order << std::endl;
    }

    std::string &get() override {
        return s;
    }
};

int func(Control& c, std::string s)
{
    c.execute(s);
}

int main(int argc, char *argv[])
{
    int i = 0;
    std::string s;
    std::vector<Control> group;
    std::vector<Ctrl1> cgroup;

    Ctrl c;
    Ctrl1 c1;

    // func(group[0], "adnasj");
    // func(group[1], "adnas1sj");
    // s = group[1].get();
    std::cout << s << std::endl;

    // while(1) {
    //     ++i;
    //     sleep(2);
    //     if(i > 5)
    //         break;
    //     fsw.execute("seq-pri");
    //     printf("0x%04x\n", fsw["ready"]);
    //     sleep(2);
    //     fsw.execute("seq-res");
    //     printf("0x%04x\n", fsw["ready"]);
    // }

    return 0;
}
