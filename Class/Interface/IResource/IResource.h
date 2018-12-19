#if !defined(_IResource_)
#define _IResource_

#include "IResourceSetterController.h"
#include "IResourceGetterController.h"

class IResource {
private:
    const std::string index;

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
    IResource(const std::string &idx) : index(idx) {

    }
    virtual ~IResource() = default;

    void bindSetterController(MrcObject<IResourceSetterController> _setterController) {
        this->setterController = std::move(_setterController);
    }

    void bindGetterController(MrcObject<IResourceGetterController> _getterController) {
        this->getterController = std::move(_getterController);
    }

    virtual bool set(const std::string &, const std::string &) = 0;
    virtual const std::string &get(const std::string &) = 0;

    const std::string &getIndex() const noexcept {
        return this->index;
    }
};

#endif // _IResource_
