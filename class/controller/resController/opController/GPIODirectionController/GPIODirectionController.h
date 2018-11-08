#if !defined(_GPIODirectionController_)
#define _GPIODirectionController_

#include <unistd.h>
#include <fcntl.h>

#include <string>

#include "../OperatorController.h"

class GPIODirectionController : public OperatorController {
private:
    static std::map<int, std::pair<int, std::string>> directioiTable;
    std::string _directoryTemplate;

    std::string &_setDirectory(const int idx) {
        return this->_directoryTemplate.replace(20, this->_directoryTemplate.find_last_of("/")-20, std::to_string(idx));
    }

    bool _isInvalid(const int idx) {
        return this->directioiTable.find(idx) != this->directioiTable.end();
    }

    bool _setDirection(const int idx, const std::string &direction) {
        if(this->_isInvalid(idx))
            return false;
        return !(write(this->fdDirection, direction.c_str(), WriteLen) < 0);
    }

    const std::string &_getDirection() {
        std::ifstream fileDirection(this->_setDirectory());
        if(!fileDirection.is_open())
            return "error";
        fileDirection >> this->_direction;
        return this->_direction;
    }

public:
    GPIODirectionController() {
    }
    ~GPIODirectionController() {
        for(auto element : this->directioiTable)
            close(element.second.first);
    }

    bool insert(const int idx) {

    }

    bool remove(const int idx) {

    }

    bool setDirection(const int idx, const std::string &direction) {
        return this->_setDirection(idx, direction);
    }

    const std::string &getDirection() {
        return this->_getDirection();
    }
};


#endif // _GPIODirectionController_
