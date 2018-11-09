#if !defined(_GPIODirectionGeter_)
#define _GPIODirectionGeter_

#include <unistd.h>
#include <fcntl.h>

#include "../../FileOperator.h"

#define DirGPIODirection "/sys/class/gpio/gpiox/direction"

class GPIODirectionGeter : public FileOperator {
private:
    std::string _direction;

public:
    GPIODirectionGeter() {
        this->_directory = DirGPIODirection;
    }
    ~GPIODirectionGeter() {

    }

    const std::string &getDirection(const int idx) {
        int fileDirectionn = open(this->_setDirectory(idx).c_str(), O_WRONLY);
        char fileContent[8];
        if(!(fileDirectionn < 0))
            if(!(read(fileDirectionn, fileContent, WRLen) < 0))
                return this->_direction.assign(fileContent);
        return "error";
    }
};

#endif // _GPIODirectionGeter_
