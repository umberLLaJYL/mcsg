#if !defined(_ResController_)
#define _ResController_

#include <string>

#include "../../resource/Resource.h"

class ResourceController {
private:
    static std::map<int, Resource*> resourceList;

public:
    ResourceController() {

    }
    ~ResourceController() {

    }

    virtual bool execute(const std::string &) = 0;
    virtual bool registerResource(Resource &res) = 0;
    virtual bool deregisterResource(Resource &res) = 0;
};

#endif // _ResController_
