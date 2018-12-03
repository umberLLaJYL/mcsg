#if !defined(_IResourceSetterControllerFactory_)
#define _IResourceSetterControllerFactory_

#include "IResourceSetter.h"
#include "../../class/resource/IResourceSetterController.h"

class IResourceSetterControllerFactory {
private:
    static MrcObject<IResourceSetterControllerFactory> resourceSetterControllerFactory;
    
public:
    IResourceSetterControllerFactory() {
        
    }
    virtual ~IResourceSetterControllerFactory() {

    }
    
    template<class... ResourceSetterControllerArgs>
    MrcObject<IResourceSetterController> create(ResourceSetterControllerArgs... argument) {
        
    }
};

#endif // _IResourceSetterControllerFactory_
