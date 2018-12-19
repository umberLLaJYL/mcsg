#if !defined(_IResourceRegister_)
#define _IResourceRegister_

#include "../MrcObject.h"

class IResourceRegister {
private:
    
public:
    IResourceRegister() {

    }
    virtual ~IResourceRegister() {

    }

    virtual bool registerResource(MrcObject<IResource> &) = 0;
    virtual bool deregisterResource(MrcObject<IResource> &) = 0;

    virtual bool isRegister(const std::string &idx) = 0;
};

#endif // _IResourceRegister_
