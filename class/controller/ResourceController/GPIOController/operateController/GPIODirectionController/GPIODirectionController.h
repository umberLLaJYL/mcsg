#if !defined(_GPIODirectionController_)
#define _GPIODirectionController_

#include <string>

#include "../../../IResourceOperationController.h"
#include "GPIODirectionOperator/GPIODirectionSeter.h"
#include "GPIODirectionOperator/GPIODirectionGeter.h"

class GPIODirectionController : public IResourceOperationController {
private:

public:
    GPIODirectionController(const std::string &idx, Object(IResourceOperationSeter)seter, Object(IResourceOperationGeter)geter) : IResourceOperationController(idx) {
        
    }
    ~GPIODirectionController() {

    }
};

#endif // _GPIODirectionController_
