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

    virtual MrcObject<IResource> create(const std::string &) = 0;
    virtual bool isRegistered(const std::string &) = 0;
    virtual bool registerResource(const std::string &) = 0;
};

#endif // _IResourceFactory_
