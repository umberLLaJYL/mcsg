#if !defined(_TEST_)
#define _TEST_

#include "ITest.h"

class Test : public ITest{
private:
public:
    Test() {

    }
    ~Test() {

    }

    void show(const std::string &str) override {
        std::cout << "Test: " << str << std::endl;
    }

};

Test test_g;

#endif // _TEST_
