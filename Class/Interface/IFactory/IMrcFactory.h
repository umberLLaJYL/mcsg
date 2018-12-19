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

    bool addFactory(const std::string &) {

    }

public:
    IMrcFactory() {

    }
    virtual ~IMrcFactory() {

    }

    bool initialize(const std::string &launchFile) {

    }

    virtual MrcObject<IMrController> create(const std::string &, const std::string &) = 0;
};

#endif // _IMrcFactory_
