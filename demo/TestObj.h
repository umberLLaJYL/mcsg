#if !defined(_TestObj_)
#define _TestObj_

#include <string>
#include <iostream>

#include "ITestObj.h"

class _TestObj : public ITestObj {
private:

public:
    _TestObj(const std::string &str) : ITestObj(str) {
        
    }
    ~_TestObj() {

    }

    void show(const std::string &str) override {
        std::cout << "TestObj->show(): " << str << std::endl;
    }
};

_TestObj TestObj("biglygylvkvkv");

#endif // _TestObj_
