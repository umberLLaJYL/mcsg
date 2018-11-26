#if !defined(_GPIO_)
#define _GPIO_

#include "../IResource.h"

class GPIO : public IResource {
public:
    GPIO(const std::string &idx) : IResource(idx) {

    }
    ~GPIO() {

    }

    bool set(const std::string &parameter, const std::string &argument) override {
        return this->_set(parameter, argument);
    }

    const std::string &get(const std::string &parameter) override {
        // return this->_get(parameter);
    }
};

#endif // _GPIO_
