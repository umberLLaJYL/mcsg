#if !defined(_GPIOIrqController_)
#define _GPIOIrqController_

#include <string>

#include "../../../IResourceOperatorController.h"
#include "GPIOIrqOperator/GPIOIrqSeter.h"
#include "GPIOIrqOperator/GPIOIrqGeter.h"

class GPIOIrqController : public IOperatorController {
private:
    GPIOIrqSeter irqSeter;
    GPIOIrqGeter irqGeter;

public:
    GPIOIrqController(const std::string &idx) : irqSeter(idx), irqGeter(idx) {

    }
    ~GPIOIrqController() {

    }

    bool setDirection(const std::string &irq) {
        return this->irqSeter.setDirection(irq);
    }

    const std::string &getDirection() {
        return this->irqGeter.getDirection();
    }
};

#endif // _GPIOIrqController_
