#if !defined(_GPIOSetter_)
#define _GPIOSetter_

#include "../../IResourceSetter.h"

#define DirGPIO "/sys/class/gpio/gpiox/"

#if !defined(WriteLen)
#define WriteLen 8
#endif // WRLen

#if !defined(WritePos)
#define WritePos 20
#endif // WritePos

class GPIOSetter : public IResourceSetter {
private:
    int handle;

protected:
    static std::string &_setDirectory(std::string &dir, const std::string &idx, const std::string &key){
        dir = DirGPIO;
        return dir.replace(WritePos, dir.find_last_of("/")-WritePos, idx) += key;
    }

    bool _setHandle(int newHandle) {
        this->handle = newHandle;
    }

    const int _getHandle() {
        return this->handle;
    }

public:
    GPIOSetter() {

    }
    virtual ~GPIOSetter() {

    }

    bool set(const std::string &direction) override {
        return !(write(this->handle, direction.c_str(), WriteLen) < 0);
    }
};

#endif // _GPIOSetter_
