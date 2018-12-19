#if !defined(_IResourceSetterController_)
#define _IResourceSetterController_

#include <map>

#include "MrcObject.h"
#include "IResourceSetter.h"

class IResourceSetterController {
private:
    std::map<std::string, MrcObject<IResourceSetter>> operationSetterList;
    std::map<std::string, MrcObject<IResourceSetter>>::iterator _setter;

protected:
    bool _set(const std::string &idx, const std::string &operation) {
        return (this->_setter = this->operationSetterList.find(idx)) == this->operationSetterList.end() ?
            false : this->_setter->second->set(operation);
    }

public:
    IResourceSetterController() {

    }
    virtual ~IResourceSetterController() {

    }

    bool addSetter(std::string &idx, MrcObject<IResourceSetter> seter) {
        return this->operationSetterList.insert({idx, seter}).second;
    }

    bool removeSetter(std::string &idx) {
        return this->operationSetterList.erase(idx) == 1;
    }

    virtual bool set(const std::string &, const std::string &) = 0;
};

#endif // _IResourceSetterController_
