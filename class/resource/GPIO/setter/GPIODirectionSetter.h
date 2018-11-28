#if !defined(_GPIODirectionSetter_)
#define _GPIODirectionSetter_

#include <map>

#include "GPIOSetter.h"

class GPIODirectionSetter : public GPIOSetter {
public:
    GPIODirectionSetter(const std::string &idx) {
        std::string dir;
        this->_setHandle(open(this->_setDirectory(dir, idx, "direction").c_str(), O_WRONLY));
    }
    ~GPIODirectionSetter() {
        close(this->_getHandle());
    }
};

#endif // _GPIODirectionSetter_
