#if !defined(_IResourceGetterController_)
#define _IResourceGetterController_

#include <map>

#include "MrcObject.h"

#include "IResourceGetter.h"

class IResourceGetterController {
private:
    std::map<std::string, MrcObject<IResourceGetter>> operationGeterList;
    std::map<std::string, MrcObject<IResourceGetter>>::iterator _geter;

public:
    IResourceGetterController() {

    }
    virtual ~IResourceGetterController() {

    }

    bool addGetter(std::string &idx, MrcObject<IResourceGetter> geter) {
        return this->operationGeterList.insert({idx, geter}).second;
    }

    const std::string &get(const std::string &operation) {

    }
};

#endif // _IResourceGetterController_
