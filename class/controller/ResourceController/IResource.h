#if !defined(_IResource_)
#define _IResource_

#include <string>
#include <vector>

#include "MrcObject.h"
#include "IResourceSetterController.h"
#include "IResourceGetterController.h"

class IResource {
private:
    const std::string index;
    MrcObject<IResourceSetterController> setter;
    MrcObject<IResourceGetterController> getter;

protected:
    bool _set(const std::string &idx, const std::string &operation) {
        return this->setter->set(idx, operation);
    }

    const std::string &_get(const std::string &idx) {
        // return this->operationController->get(idx);
    }

public:
    IResource(const std::string &idx) : index(idx) {

    }
    virtual ~IResource() = default;

    virtual bool set(const std::string &, const std::string &) = 0;
    virtual const std::string &get(const std::string &) = 0;

    const std::string &getIndex() const {
        return this->index;
    }
};

#endif // _IResource_
