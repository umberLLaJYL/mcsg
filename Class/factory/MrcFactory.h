#if !defined(_MrcFactory_)
#define _MrcFactory_

#include "../Interface/Ifactory/IMrcFactory.h"

class MrcFactory : public IMrcFactory {
private:
    MrcObject<DirectoryReader> directoryReader;

public:
    MrcFactory(const std::string &dir) : IMrcFactory(dir) {

    }
    ~MrcFactory() {

    }

    // MrcObject<IMrController> create(const std::string &type) override {
        
    // }
};

#endif // _MrcFactory_
