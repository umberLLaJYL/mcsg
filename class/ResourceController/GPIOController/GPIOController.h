#if !defined(_GPIOController_)
#define _GPIOController_

#include "../../resource/GPIO/GPIO.h"
#include "../IResourceController.h"
#include "GPIORegister.h"

class GPIOController : public IResourceController {
private:

public:
    GPIOController() {

    }
    ~GPIOController() {

    }

    bool execute(const std::string &sequence) override {

    }

    bool addResource(MrcObject<IResource> res) override {

    }

    bool removeResource(const std::string &idx) override {
        
    }

    bool setDirection(const int idx, const std::string &direction) {
        
    }

    const std::string &getDirection(const int idx) {

    }
};

#endif // _GPIOController_
