#if !defined(_GPIORegister_)
#define _GPIORegister_

#include "GPIOExporter.h"
#include "../../IResourceRegister.h"

class GPIORegister : public IResourceRegister<GPIO> {
private:
    static GPIOExporter exporter;

public:
    GPIORegister() {

    }
    ~GPIORegister() {

    }

    bool registerResource(GPIO *gpio) override {
        return this->addResource(gpio);
    }
    bool deregisterResource(const std::string &idx) override {
        
    }
};

GPIOExporter _exporter;
GPIOExporter GPIORegister::exporter = _exporter;

#endif // _GPIORegister_
