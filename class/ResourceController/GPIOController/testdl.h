#if !defined(_TESTDL_)
#define _TESTDL_

#include "test.h"

// #include <dlfcn.h>

class TestDl : public Test {
private:

public:
    TestDl() {

    }
    ~TestDl() {

    }

    void show(const std::string &str) override {
        std::cout << "class TestDl: " << str << std::endl;
    }
};

#endif // _TESTDL_
