#if !defined(_IResourceFactory_)
#define _IResourceFactory_

#include "IResourceSetterControllerFactory.h"
#include "../resource/IResource.h"

class IResourceFactory {
private:

public:
    IResourceFactory() {

    }
    virtual ~IResourceFactory() {

    }

    virtual MrcObject<IResource> create(const std::string &) = 0;
    // virtual MrcObject<IResourceSetterController> createSetterController() = 0;
    // virtual MrcObject<IResourceSetter> createSetter() = 0;
};

#endif // _IResourceFactory_
