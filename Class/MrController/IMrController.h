#if !defined(_IMrController_)
#define _IMrController_

#include "../MrcObject.h"
#include "../resource/IResource.h"

class IMrController {
private:

public:
    IMrController() {

    }
    virtual ~IMrController() {

    }

    virtual bool execute(const std::string &) = 0;
};

#endif // _IMrController_
