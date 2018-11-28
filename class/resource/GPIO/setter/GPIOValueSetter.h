#if !defined(_GPIODirectionSeter_)
#define _GPIODirectionSeter_

#include <map>

#include "../../../../IFileOperator.h"

class GPIODirectionSeter : public IFileOperator {
private:
    int fileDirection;

public:
    GPIODirectionSeter(const std::string &idx) {
        std::string dir;
        fileDirection = open(this->_setDirectory(dir, idx).c_str(), O_WRONLY);
    }
    ~GPIODirectionSeter() {
        close(this->fileDirection);
    }

    bool setDirection(const std::string &direction) {
        return (!write(this->fileDirection, direction.c_str(), WRLen) < 0);
    }
};

#endif // _GPIODirectionSeter_
