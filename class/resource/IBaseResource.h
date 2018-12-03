#if !defined(_IBaseResource_)
#define _IBaseResource_

#include <string>

#include "../MrcObject.h"

class IBaseResource {
    const std::string index;

public:
    IBaseResource(const std::string &) {

    }
    virtual ~IBaseResource() = default;

    virtual bool set(const std::string &, const std::string &) = 0;
    virtual const std::string &get(const std::string &) = 0;

    const std::string &getIndex() const {
        return this->index;
    }
};

#endif // _IBaseResource_
