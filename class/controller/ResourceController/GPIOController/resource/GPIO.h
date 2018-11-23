#if !defined(_GPIO_)
#define _GPIO_

#include "../../IResource.h"

class GPIO : public IResource {
private:

public:
    GPIO(const std::string &idx) : IResource(idx) {

    }
    ~GPIO() {

    }

    bool set(const std::string &idx, const std::string &operation) override {
        return this->_set(idx, operation);
    }

    const std::string &get(const std::string &idx) override {

    }
};

#endif // _GPIO_
