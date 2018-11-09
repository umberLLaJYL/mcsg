#if !defined(_GPIODirectionSeter_)
#define _GPIODirectionSeter_

#include <map>

#include "../../FileOperator.h"

class GPIODirectionSeter : public FileOperator {
private:
    static std::map<int, int> flieList;

public:
    GPIODirectionSeter() {

    }
    ~GPIODirectionSeter() {
        for(auto element : this->flieList)
            close(element.second);
    }

    bool insert(const int idx) {
        int fileDirection = open(this->_setDirectory(idx).c_str(), O_WRONLY);
        return fileDirection < 0 ? false : this->flieList.insert({idx, fileDirection}).second;
    }

    bool remove(const int idx) {
        close(this->flieList.find(idx)->second);
        return this->flieList.erase(idx) == 1;
    }

    bool setDirection(const int idx, const std::string &direction) {
        return!(write(this->flieList.find(idx)->second, direction.c_str(), WRLen) < 0);
    }
};

#endif // _GPIODirectionSeter_
