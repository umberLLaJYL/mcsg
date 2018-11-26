#if !defined(_IResourceSetterController_)
#define _IResourceSetterController_

#include <map>

#include "MrcObject.h"

#include "IResourceOperationSeter.h"
#include "IResourceOperationGeter.h"

class IResourceSetterController {
private:
    std::map<std::string, MrcObject<IResourceOperationSeter>> operationSeterList;
    std::map<std::string, MrcObject<IResourceOperationSeter>>::iterator _seter;

public:
    IResourceSetterController() {

    }
    virtual ~IResourceSetterController() {

    }

    bool addSetter(std::string &idx, MrcObject<IResourceOperationSeter> seter) {
        return this->operationSeterList.insert({idx, seter}).second;
    }

    bool removeSetter(std::string &idx) {
        return this->operationSeterList.erase(idx) == 1;
    }

    bool set(const std::string &idx, const std::string &operation) {
        return (this->_seter = this->operationSeterList.find(idx)) == this->operationSeterList.end() ?
            false : this->_seter->second->set(operation);
    }
};

#endif // _IResourceSetterController_
