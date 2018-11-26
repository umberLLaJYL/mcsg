#if !defined(_IResourceGeter_)
#define _IResourceGeter_

#include <unistd.h>
#include <fcntl.h>

#include <string>

class IResourceGeter {
private:

public:
    IResourceGeter(const std::string &) {

    }
    virtual ~IResourceGeter() {

    }

    virtual const std::string &get() = 0;
};

#endif // _IResourceGeter_
