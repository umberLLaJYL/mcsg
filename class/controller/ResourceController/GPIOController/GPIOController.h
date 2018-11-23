#if !defined(_GPIOController_)
#define _GPIOController_

#include "resource/GPIO.h"
#include "GPIORegister/GPIORegister.h"
#include "../IResourceController.h"

class GPIOController : public IResourceController {
private:

public:
    GPIOController() {

    }
    ~GPIOController() {

    }

    bool execute(const std::string &cmd) override {

    }

    // bool setDirection(const int idx, const std::string &direction) {
    //     return this->GPIOList.find(idx)->;
    // }

    // const std::string &getDirection(const int idx) {
    //     return this->GPIOList.getDirection(idx);
    // }
};

#endif // _GPIOController_
