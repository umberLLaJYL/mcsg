#if !defined(_IResourceSetter_)
#define _IResourceSetter_

#include <unistd.h>
#include <fcntl.h>

#include <string>

#define DirGPIO "/sys/class/gpio/gpiox/"

#if !defined(WRLen)
#define WRLen 8
#endif // WRLen

#if !defined(WritePos)
#define WritePos 20
#endif // WritePos

class IResourceSetter {
private:
    
protected:
    std::string &_setDirectory(std::string &dir, const std::string &idx, const std::string &key){
        dir = DirGPIO;
        return dir.replace(WritePos, dir.find_last_of("/")-WritePos, idx) += key;
    }

public:
    IResourceSetter() {

    }
    virtual ~IResourceSetter() {

    }

    virtual bool set(const std::string &) = 0;
};

#endif // _IResourceSetter_
