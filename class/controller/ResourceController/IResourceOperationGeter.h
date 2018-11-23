#if !defined(_IResourceOperationGeter_)
#define _IResourceOperationGeter_

#include <unistd.h>
#include <fcntl.h>

#include <string>

#define DirGPIO "/sys/class/gpio/gpiox/"

#if !defined(WRLen)
#define WRLen 8
#endif // WRLen

#if !defined(WritePos)
#define WritePos 20
#endif // WritePos

class IResourceOperationGeter {
private:

public:
    IResourceOperationGeter(const std::string &) {

    }
    virtual ~IResourceOperationGeter() {

    }

    virtual const std::string &get() = 0;
};

#endif // _IResourceOperationGeter_
