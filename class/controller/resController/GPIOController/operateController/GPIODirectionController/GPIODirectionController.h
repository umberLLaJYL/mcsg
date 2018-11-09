#if !defined(_GPIODirectionController_)
#define _GPIODirectionController_

#include <string>

#include "../OperatorController.h"
#include "GPIODirectionSeter.h"
#include "GPIODirectionGeter.h"

class GPIODirectionController : public OperatorController {
private:
    static GPIODirectionSeter directionSeter;
    static GPIODirectionGeter directionGeter;

public:
    GPIODirectionController() {

    }
    ~GPIODirectionController() {

    }

    bool setDirection(const int idx, const std::string &direction) {
        return this->directionSeter.setDirection(idx, direction);
    }

    const std::string &getDirection(const int idx) {
        return this->directionGeter.getDirection(idx);
    }
};

#endif // _GPIODirectionController_
