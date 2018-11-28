#if !defined(_GPIO_)
#define _GPIO_

#include "IResource.h"

class GPIO : public IResource {
public:
    GPIO(const std::string &idx, MrcObject<IResourceSetterController> setter, MrcObject<IResourceGetterController> getter) : IResource::IResource(idx, setter, getter) {

    }
    ~GPIO() {

    }

    bool set(const std::string &parameter, const std::string &argument) override {
        return this->_set(parameter, argument);
    }

    const std::string &get(const std::string &parameter) override {
        return this->_get(parameter);
    }

    bool setValue(const std::string &argument) {
        return this->_set("GPIOValue", argument);
    }

    const std::string &getValue() {
        return this->_get("GPIOValue");
    }
};

#endif // _GPIO_
