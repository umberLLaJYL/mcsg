#if !defined(_ITestObj_)
#define _ITestObj_

#include <string>
#include <iostream>

class ITestObj {
private:
    const std::string idx;

public:
    ITestObj(const std::string &str) : idx(str) {
        
    }
    virtual ~ITestObj() {

    }

    void getIndex() {
        std::cout << this->idx << std::endl;
    }
    
    virtual void show(const std::string &str) = 0;
};

#endif // _ITestObj_
