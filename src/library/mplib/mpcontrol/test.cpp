#include "control.h"
#include "../rapidjson/rapidjson.h"
#include "../rapidjson/document.h"

int main(int argc, char *argv[])
{
    std::string line;
    std::ifstream configFile("./fsw1.json");

    while(std::getline(configFile, line)){
        std::cout << line+'\n';
    }    
    // while(1) {

    // }
    
    return 0;
}
