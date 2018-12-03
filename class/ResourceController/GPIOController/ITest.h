#if !defined(_ITEST_)
#define _ITEST_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>

class ITest {
private:

public:
    ITest() {

    }
    ~ITest() {

    }

    virtual void show(const std::string &) = 0;
};

#endif
