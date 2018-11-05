#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include <unistd.h>
#include <fcntl.h>

// #include "pin/pin.h"
// #include "adc/adc.h"
// #include "dac/dac.h"
// #include "serial/serial.h"
#include "../../json/rapidjson/document.h"

using namespace rapidjson;

#define GPIODir "/sys/class/gpio/gpio/direction"
#define PinAct(action) GPIODir#action

const char *func()
{
    std::string str;
    
    std::ifstream iodir((str = GPIODir) += std::to_string(66) += "/direction");
    iodir >> str;

    return str.c_str();
}

const bool func1(const int idx, const std::map<int, std::pair<int, std::string>> &table)
{
    auto element = table.find(idx);
    return element != table.end();
}


class Test {
private:
    std::string str;
    std::map<std::string, std::string> table;

public:
    Test(/* args */) {
        this->str = "asdf";
        this->table.insert({"bb", "dd"});
    }
    ~Test() { }

    void function() {
        
    }

    // template<class Controller>
    // Controller &bind() {
    //     return this->str;
    // }
};

int main(int argc, char *argv[])
{
    std::string str(GPIODir);
    int i = 9, fd;

    // std::ofstream ofs("/sys/class/gpio/unexport");

    device.addController<GPIOController>(controllerFactory.createController("fsw1.json"));



    str.replace(20, str.find_last_of("/")-20, std::to_string(65));

    std::cout << str << std::endl;

    // if(write(fd, "88", 8) < 0)
    //     perror("w");

    // ofs << "88";

    // str = test.bind<std::string>();

    // printf("i: %s\n", str.c_str());

    // while(1) {
    //     ++i;
    //     sleep(2);
    //     if(i > 5)
    //         break;
    //     fsw.execute("seq-pri");
    //     printf("0x%04x\n", fsw["ready"]);
    //     sleep(2);
    //     fsw.execute("seq-res");
    //     printf("0x%04x\n", fsw["ready"]);
    // }

    return 0;
}
