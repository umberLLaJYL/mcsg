#if !defined(_GPIODirectionSetter_)
#define _GPIODirectionSetter_

#include <map>

#include "../../IResourceSetter.h"

class GPIODirectionSetter : public IResourceSetter {
private:
    int fileDirection;

public:
    GPIODirectionSetter(const std::string &idx) {
        std::string dir;
        fileDirection = open(this->_setDirectory(dir, idx, "direction").c_str(), O_WRONLY);
    }
    ~GPIODirectionSetter() {
        close(this->fileDirection);
    }

    bool set(const std::string &direction) override {
        return !(write(this->fileDirection, direction.c_str(), WRLen) < 0);
    }
};

#endif // _GPIODirectionSetter_
