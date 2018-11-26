#if !defined(_IResourceGetterController_)
#define _IResourceGetterController_

#include <map>

#include "MrcObject.h"

#include "IResourceOperationSetter.h"
#include "IResourceOperationGetter.h"

class IResourceGetterController {
private:
    std::map<std::string, MrcObject<IResourceOperationGeter>> operationGeterList;
    std::map<std::string, MrcObject<IResourceOperationGeter>>::iterator _geter;

public:
    IResourceGetterController() {

    }
    virtual ~IResourceGetterController() {

    }

    bool addGetter(std::string &idx, MrcObject<IResourceOperationGeter> geter) {
        return this->operationGeterList.insert({idx, geter}).second;
    }

    const std::string &get(const std::string &operation) {

    }
};

#endif // _IResourceGetterController_
