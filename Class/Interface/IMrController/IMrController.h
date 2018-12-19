#if !defined(_IMrcController_)
#define _IMrcController_

#include <map>
#include <string>

#include "../../MrcObject.h"

#define DirMrController "./MrController.json"

class IMrController {
private:
    std::map<std::string, MrcObject<IResourceController>> resController;

public:
    IMrController() {

    }
    virtual ~IMrController() {

    }

    void createController(const std::string &cfgFile);
    bool destroyController(const std::string &idx);

    virtual MrcObject<IResource> &requestResource(const std::string &, const std::string &) = 0;
    virtual MrcObject<IResource> &withdrawResource(const std::string &) = 0;
};

#endif // _IMrcController_
