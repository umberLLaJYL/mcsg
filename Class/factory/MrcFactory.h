#if !defined(_MrcFactory_)
#define _MrcFactory_

#include "../Interface/Ifactory/IMrcFactory.h"

#include "DirectoryReader.h"

class MrcFactory : public IMrcFactory {
private:
    MrcObject<DirectoryReader> directoryReader;

public:
    MrcFactory() {

    }
    ~MrcFactory() {

    }

    MrcObject<IMrController> create(const std::string &type) override {
        
    }
};

#endif // _MrcFactory_
