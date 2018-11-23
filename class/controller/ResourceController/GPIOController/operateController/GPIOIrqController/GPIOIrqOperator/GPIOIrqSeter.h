#if !defined(_GPIOIrqSeter_)
#define _GPIOIrqSeter_

#include <map>

#include "../../../../IFileOperator.h"

class GPIOIrqSeter : public IFileOperator {
private:
    int fileIrq;

public:
    GPIOIrqSeter(const std::string &idx) {
        std::string dir;
        fileIrq = open(this->_setDirectory(dir, idx, "irq").c_str(), O_WRONLY);
    }
    ~GPIOIrqSeter() {
        close(this->fileIrq);
    }

    bool setDirection(const std::string &direction) {
        return (!write(this->fileIrq, direction.c_str(), WRLen) < 0);
    }
};

#endif // _GPIOIrqSeter_
