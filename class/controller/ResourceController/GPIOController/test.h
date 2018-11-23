#if !defined(_TEST_)
#define _TEST_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <memory>

class Test {
private:

public:
    Test() {

    }
    ~Test() {

    }

    virtual void show(const std::string &) = 0;
};

#endif // _TEST_
