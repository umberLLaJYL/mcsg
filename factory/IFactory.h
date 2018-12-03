#if !defined(_IFACTORY_)
#define _IFACTORY_

#include <dlfcn.h>

#include <map>
#include <string>

#include "IReader.h"
#include "../class/MrcObject.h"

class IFactory {
private:
    MrcObject<IReader> reader;
    
public:
    IFactory() {

    }
    virtual ~IFactory() {

    }
};

#endif // _IFACTORY_
