#if !defined(_IResourceRegister_)
#define _IResourceRegister_

#include <map>

#include "MrcObject.h"

class IResourceRegister {
private:
    static int fileRegister;
    
protected:
    static std::map<std::string, MrcObject<IResource>> resourceList;

    bool addResource(MrcObject<IResource> res) {
        this->resourceList.insert({res->getIndex(), res});
    }

    bool remove(const std::string idx) {
        auto element = this->resourceList.find(idx);
        return element == this->resourceList.end() ? false : this->resourceList.erase(idx) == 1;
    }

public:
    IResourceRegister() {

    }
    ~IResourceRegister() {
        
    }

    virtual bool registerResource(MrcObject<IResource>) = 0;
    virtual bool deregisterResource(const std::string &) = 0;
};

#endif // _IResourceRegister_
