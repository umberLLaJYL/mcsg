#if !defined(_TESTSO_)
#define _TESTSO_

#include "test.h"

// #include <dlfcn.h>

class TestSo : public Test {
private:

public:
    TestSo() {

    }
    ~TestSo() {

    }

    void show(const std::string &str) override {
        std::cout << "class TestSO: " << str << std::endl;
    }
};

#endif // _TESTSO_
