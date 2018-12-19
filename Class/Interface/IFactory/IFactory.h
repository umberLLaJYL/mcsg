#if !defined(_IFACTORY_)
#define _IFACTORY_

#include <map>
#include <string>

#include "IResourceFactory/IResourceFactory.h"
#include "IReader.h"
#include "../Class/MrcObject.h"

class IFactory {
private:
    MrcObject<IReader> reader;
    
protected:

public:
    IFactory() {

    }
    virtual ~IFactory() {

    }
};

#endif // _IFACTORY_
