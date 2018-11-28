#if !defined(_GPIOValueGeter_)
#define _GPIOValueGeter_

#include "../../../../IFileOperator.h"

class GPIOValueGeter : public IFileOperator {
private:
    std::string _directory;
    std::string _value;
    
public:
    GPIOValueGeter(const std::string &idx) {
        std::string dir;
        this->_directory = this->_setDirectory(dir, idx, "value").c_str();
    }
    ~GPIOValueGeter() {

    }

    const std::string &getDirection() {
        int fileValue = open(this->_directory.c_str(), O_WRONLY);
        char fileContent[8];
        if(!(fileValue < 0))
            return read(fileValue, fileContent, WRLen) < 0 ?
                this->_value.assign("error") :
                this->_value.assign(fileContent);
    }
};

#endif // _GPIOValueGeter_
