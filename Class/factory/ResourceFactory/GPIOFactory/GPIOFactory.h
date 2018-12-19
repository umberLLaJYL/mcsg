#if !defined(_GPIOFactory_)
#define _GPIOFactory_

#include "../../../class/resource/GPIO/GPIO.h"
#include "../IResourceFactory.h"

class GPIOFactory : public IResourceFactory {
private:

public:
    GPIOFactory() {

    }
    ~GPIOFactory() {

    }

    MrcObject<IResource> create(const std::string &idx) override {
        return MrcObject<GPIO>::make_shared(idx);
    }
};

#endif // _GPIOFactory_
