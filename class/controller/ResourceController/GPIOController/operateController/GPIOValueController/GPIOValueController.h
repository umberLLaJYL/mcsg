#if !defined(_GPIOValueController_)
#define _GPIOValueController_

#include <string>

#include "../../../IResourceOperatorController.h"
#include "GPIOValueOperator/GPIOValueSeter.h"
#include "GPIOValueOperator/GPIOValueGeter.h"

class GPIOValueController : public IOperatorController {
private:
    GPIOValueSeter valueSeter;
    GPIOValueSeter valueGeter;

public:
    GPIOValueController(const std::string &idx) : valueSeter(idx), valueGeter(idx) {

    }
    ~GPIOValueController() {

    }

    bool setDirection(const std::string &value) {
        return this->valueSeter.setDirection(value);
    }

    const std::string &getDirection() {
        return this->valueSeter.getDirection();
    }
};

#endif // _GPIOValueController_
