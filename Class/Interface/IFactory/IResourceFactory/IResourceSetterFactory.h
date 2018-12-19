#if !defined(_IResourceSetterFactory_)
#define _IResourceSetterFactory_

#include "../../class/MrcObject.h"
#include "../../class/resource/IResourceSetter.h"

class IResourceSetterFactory {
private:

public:
    IResourceSetterFactory() {

    }
    virtual ~IResourceSetterFactory() {

    }

    virtual MrcObject<IResourceSetter> create() = 0;
};

#endif // _IResourceSetterFactory_
