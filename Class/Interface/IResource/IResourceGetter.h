#if !defined(_IResourceGeter_)
#define _IResourceGeter_

#include <unistd.h>
#include <fcntl.h>

#include <string>

class IResourceGetter {
private:

public:
    IResourceGetter() {

    }
    virtual ~IResourceGetter() {

    }

    virtual const std::string &get() = 0;
};

#endif // _IResourceGeter_
