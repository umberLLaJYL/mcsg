#if !defined(_GPIODirectionGeter_)
#define _GPIODirectionGeter_

#include "../../IResourceGetter.h"

class GPIODirectionGeter : public IResourceGetter {
private:
    std::string _directory;
    std::string _direction;
    
    const std::string &getDirection() {
        int fileDirection = open(this->_directory.c_str(), O_WRONLY);
        char fileContent[8];
        if(!(fileDirection < 0))
            return read(fileDirection, fileContent, WriteLen) < 0 ?
                this->_direction.assign("error") :
                this->_direction.assign(fileContent);
    }

public:
    GPIODirectionGeter(const std::string &idx) {
        this->_setDirectory(this->_directory, idx, "direction");
    }
    ~GPIODirectionGeter() {

    }

    const std::string &get() override {
        return this->getDirection();
    }
};

#endif // _GPIODirectionGeter_
