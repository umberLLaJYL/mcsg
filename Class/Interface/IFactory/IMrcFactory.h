#if !defined(_IMrcFactory_)
#define _IMrcFactory_

#include "IFactory.h"

#include "../IMrController/IMrController.h"

#if !defined(MrcObject)
#define MrcObject std::shared_ptr
#endif // MrcObject

class IMrcFactory {
private:
    std::map<std::string, MrcObject<IResourceFactory>> resFactory;

public:
    IMrcFactory() {

    }
    virtual ~IMrcFactory() {

    }

    // virtual bool initialize(const std::string &launchFile) {
        
    // }

    bool addFactory(MrcObject<IResourceFactory> &factory) {
        return this->resFactory.insert({"", factory}).second;
    }

    virtual MrcObject<IMrController> create(const std::string &) = 0;
};

#endif // _IMrcFactory_
