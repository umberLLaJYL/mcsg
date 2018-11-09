#if !defined(_GPIOController_)
#define _GPIOController_

#include <map>

#include "resource/GPIO.h"

class GPIOController : public ResourceController {
private:
    static const int registerFile;
    static std::map<int, GPIO> GPIOList;

    bool registerGPIO(const int idx) {

    }

    bool deregisterGPIO(const int idx) {

    }

    bool exportGPIO(const int idx) {

    }

    bool unexportGPIO(const int idx) {

    }

public:
    GPIOController() = default;
    ~GPIOController();

    bool execute(const std::string &cmd) override {

    }

    bool registerResource(Resource &res) override {

    }

    bool deregisterResource(Resource &res) override {

    }

    bool setDirection(const int idx, const std::string &direction) {
        return this->GPIOList.find(idx)->;
    }

    const std::string &getDirection(const int idx) {
        return this->GPIOList.getDirection(idx);
    }
};

#endif // _GPIOController_
