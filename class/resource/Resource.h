#if !defined(_Resource_)
#define _Resource_

#include "IBaseResource.h"

class Resource : public IBaseResource {
public:
    Resource(const std::string idx) : IBaseResource::IBaseResource(idx) {

    }
    virtual ~Resource() = default;
};

#endif // _Resource_
