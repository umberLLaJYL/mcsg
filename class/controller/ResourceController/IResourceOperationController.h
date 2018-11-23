#if !defined(_IResourceOperationController_)
#define _IResourceOperationController_

#include <map>

#include "Object.h"

#include "IResourceOperationSeter.h"
#include "IResourceOperationGeter.h"

class IResourceOperationController {
private:
    std::map<std::string, Object(IResourceOperationSeter)> operationSeter;
    std::map<std::string, Object(IResourceOperationGeter)> operationGeter;

public:
    IResourceOperationController() {

    }
    virtual ~IResourceOperationController() {

    }

    bool _bind(std::string &, Object(IResourceOperationSeter)) {

    }

    bool _bind(std::string &, Object(IResourceOperationGeter)) {
        
    }

    bool set(const std::string &idx, const std::string &operation) {
        return this->operationSeter.find(idx)->second->set(operation);
    }

    const std::string &get() {
        return this->operationGeter->get();
    }
};

#endif // _IResourceOperationController_
