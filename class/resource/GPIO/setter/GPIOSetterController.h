#if !defined(_GPIOSetterController_)
#define _GPIOSetterController_

#include "../../IResourceSetterController.h"

class GPIOSetterController : public IResourceSetterController {
private:

public:
    GPIOSetterController() {

    }
    ~GPIOSetterController() {

    }

    bool set(const std::string &parameter, const std::string &argument) override {
        return this->_set(parameter, argument);
    }
};

#endif // _GPIOSetterController_
