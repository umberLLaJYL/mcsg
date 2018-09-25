#include <fstream>
#include "control.h"

IoControl::IoControl(const std::string &dir) : status(-1)
{
    std::ifstream configFile(dir);
    std::string line;
    std::string file;

    while(std::getline(configFile, line))
        file += line;
}

IoControl::~IoControl()
{

}
