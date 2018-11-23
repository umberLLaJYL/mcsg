#if !defined(_GPIODirectionSeter_)
#define _GPIODirectionSeter_

#include <map>

#include "../../../../IResourceOperationSeter.h"

class GPIODirectionSeter : public IResourceOperationSeter {
private:
    int fileDirection;

public:
    GPIODirectionSeter(const std::string &idx) {
        std::string dir;
        fileDirection = open(this->_setDirectory(dir, idx, "direction").c_str(), O_WRONLY);
    }
    ~GPIODirectionSeter() {
        close(this->fileDirection);
    }

    bool set(const std::string &direction) override {
        return !(write(this->fileDirection, direction.c_str(), WRLen) < 0);
    }
};

#endif // _GPIODirectionSeter_
