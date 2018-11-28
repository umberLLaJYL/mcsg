#if !defined(_GPIORegister_)
#define _GPIORegister_

#include <set>

#include "../../../resource/IResource.h"
#include "../IResourceRegister.h"

class GPIORegister : public IResourceRegister {
private:
    static int GPIORegisterHandle;
    static std::set<std::string> registerTable;

public:
    GPIORegister() {

    }
    ~GPIORegister() {

    }

    bool registerResource(MrcObject<IResource> &res) override {
        return this->registerTable.insert(res->getIndex()).second;
    }

    bool deregisterResource(MrcObject<IResource> &res) override {
        return this->registerTable.erase(res->getIndex()) == 1;
    }

    bool isRegister(const std::string &idx) {

    }
};

int GPIORegister::GPIORegisterHandle = open("./reg/gpio.json", O_RDWR);

#endif // _GPIORegister_
