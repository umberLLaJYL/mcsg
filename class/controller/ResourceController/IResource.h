#if !defined(_IResource_)
#define _IResource_

#include <string>
#include <vector>

#include "Object.h"
#include "IResourceOperationController.h"

class IResource {
private:
    const std::string index;
    Object(IResourceOperationController) operationController;

protected:
    bool _set(const std::string &idx, const std::string &operation) {
        return this->operationController->set(idx, operation);
    }

    const std::string &_get(const std::string &operation) {
        return this->operationController->get();
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
