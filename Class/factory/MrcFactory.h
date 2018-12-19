#if !defined(_MrcFactory_)
#define _MrcFactory_

#include "../Interface/Ifactory/IMrcFactory.h"

#include "DirectoryReader.h"

class MrcFactory : private IMrcFactory {
private:


public:
    MrcFactory() {

    }
    ~MrcFactory() {

    }

    MrcObject<IMrController> create(const std::string &type, const std::string &idx) override {

    }
};

#endif // _MrcFactory_
