#if !defined(_GPIOIrqGeter_)
#define _GPIOIrqGeter_

#include "../../../../IFileOperator.h"

class GPIOIrqGeter : public IFileOperator {
private:
    std::string _directory;
    std::string _direction;
    
public:
    GPIOIrqGeter(const std::string &idx) {
        std::string dir;
        this->_directory = this->_setDirectory(dir, idx, "irq").c_str();
    }
    ~GPIOIrqGeter() {

    }

    const std::string &getDirection() {
        int fileIrq = open(this->_directory.c_str(), O_WRONLY);
        char fileContent[8];
        if(!(fileIrq < 0))
            return read(fileIrq, fileContent, WRLen) < 0 ?
                this->_direction.assign("error") :
                this->_direction.assign(fileContent);
    }
};

#endif // _GPIOIrqGeter_
