#if !defined(_IResourceController_)
#define _IResourceController_

#include "IResourceRegister.h"

class IResourceController {
private:
    MrcObject<IResourceRegister> resRegister;

public:
    IResourceController() {

    }
    virtual ~IResourceController() = 0;

    virtual bool execute(const std::string &) = 0;
};

#endif // _IResourceController_
