#include "control.h"

int main(int argc, char *argv[])
{
    std::string dir("/fsw1.mcsg");
    std::string line;
    std::ifstream configFile(dir);

    while(std::getline(configFile, line)){
        std::cout << line;
    }    
    // while(1) {

    // }
    
    return 0;
}
