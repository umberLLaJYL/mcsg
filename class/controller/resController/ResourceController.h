#if !defined(_ResController_)
#define _ResController_

#include <string>

class ResourceController {
private:

public:
    ResourceController() {

    }
    ~ResourceController() {

    }

    virtual bool execute(const std::string &) = 0;
};

#endif // _ResController_
