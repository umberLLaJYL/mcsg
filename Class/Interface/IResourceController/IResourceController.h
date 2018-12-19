#if !defined(_IResourceController_)
#define _IResourceController_

#include "../resource/IResource.h"
#include "IResourceRegister.h"

class IResourceController {
private:
    std::map<std::string, MrcObject<IResource>> resourceList;
    MrcObject<IResourceRegister> resRegister;

public:
    IResourceController() {

    }
    virtual ~IResourceController() {

    }

    virtual bool execute(const std::string &) = 0;
    virtual bool addResource(MrcObject<IResource>) = 0;
    virtual bool removeResource(const std::string &idx) = 0;
};

#endif // _IResourceController_
