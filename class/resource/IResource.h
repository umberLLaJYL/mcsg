#if !defined(_IResource_)
#define _IResource_

#include <vector>

#include "IBaseResource.h"
#include "IResourceSetterController.h"
#include "IResourceGetterController.h"

class IResource : public IBaseResource {
private:
    MrcObject<IResourceSetterController> setterController;
    MrcObject<IResourceGetterController> getterController;

protected:
    bool _set(const std::string &parameter, const std::string &argument) {
        return this->setterController->set(parameter, argument);
    }

    const std::string &_get(const std::string &parameter) {
        return this->getterController->get(parameter);
    }

public:
    IResource(const std::string &idx) : IBaseResource::IBaseResource(idx) {

    }
    virtual ~IResource() = default;

    void bindSetterController(MrcObject<IResourceSetterController> _setterController) {
        this->setterController = std::move(_setterController);
    }

    void bindGetterController(MrcObject<IResourceGetterController> _getterController) {
        this->getterController = std::move(_getterController);
    }
};

#endif // _IResource_
