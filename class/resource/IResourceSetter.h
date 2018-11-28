#if !defined(_IResourceSetter_)
#define _IResourceSetter_

#include <unistd.h>
#include <fcntl.h>

#include <string>

class IResourceSetter {
private:

public:
    IResourceSetter() {

    }
    virtual ~IResourceSetter() {

    }

    virtual bool set(const std::string &) = 0;
};

#endif // _IResourceSetter_
