#if !defined(_IResourceFactory_)
#define _IResourceFactory_

#include "../resource/IResource.h"

class IResourceFactory {
private:
    
public:
    IResourceFactory() {

    }
    virtual ~IResourceFactory() {

    }

    virtual MrcObject<IResource> create(const std::string &, MrcObject<IResourceSetterController>, MrcObject<IResourceGetterController>) = 0;
};

#endif // _IResourceFactory_
