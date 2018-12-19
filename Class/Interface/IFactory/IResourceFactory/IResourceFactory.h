#if !defined(_IResourceFactory_)
#define _IResourceFactory_

#include "IResourceSetterControllerFactory.h"
#include "../../IResource/IResource.h"

class IResourceFactory {
private:

public:
    IResourceFactory() {

    }
    virtual ~IResourceFactory() {

    }

    MrcObject<IResource> create(const std::string &idx) {
        
    }
};

#endif // _IResourceFactory_
