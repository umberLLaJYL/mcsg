#if !defined(_GPIOExporter_)
#define _GPIOExporter_

#include <unistd.h>
#include <fcntl.h>

#include <string>

#define WriteLen 8
#define DirGPIO "/sys/class/gpio/gpio"
#define DirGPIODirection "/sys/class/gpio/gpiox/direction"

#define dirExport(action) DirGPIO#action

class GPIOExporter {
private:
    static const int fileExport, fileUnexport;
    
public:
    GPIOExporter() {

    }
    ~GPIOExporter() {
        close(this->fileExport);
        close(this->fileUnexport);
    }

    bool exportGPIO(const int idx) {
        return !(write(this->fileExport, std::to_string(idx).c_str(), WriteLen) < 0);
    }

    bool unexportGPIO(const int idx) {
        return !(write(this->fileUnexport, std::to_string(idx).c_str(), WriteLen) < 0);
    }
};

const int GPIOExporter::fileExport = open(dirExport(/export), O_WRONLY);
const int GPIOExporter::fileUnexport = open(dirExport(/unexport), O_WRONLY);

#endif // _GPIOExporter_
