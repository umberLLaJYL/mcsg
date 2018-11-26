#if !defined(_IResourceGetterController_)
#define _IResourceGetterController_

#include <map>

#include "MrcObject.h"

#include "IResourceOperationSeter.h"
#include "IResourceOperationGeter.h"

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

    bool get(const std::string &idx, const std::string &operation) {

    }
};

#endif // _IResourceGetterController_
