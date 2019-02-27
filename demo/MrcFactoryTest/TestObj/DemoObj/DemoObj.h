#if !defined(_DemoObj_)
#define _DemoObj_

#include <string>
#include <iostream>

#include "../ITestObj.h"

class _DemoObj : public ITestObj {
private:

public:
    _DemoObj(const std::string &str) : ITestObj(str) {
        
    }
    ~_DemoObj() {

    }

    void show(const std::string &str) override {
        std::cout << "DemoObj->show(): " << str << std::endl;
    }
};

_DemoObj DemoObj("dshushisvn");

#endif // _DemoObj_
