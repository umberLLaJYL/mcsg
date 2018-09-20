#include <fstream>
#include "control.h"

IoControl::IoControl(const std::string &dir) : status(-1)
{
    std::ifstream configFile(dir);
    std::string line;

    while(std::getline(configFile, line)){

    }
}

IoControl::~IoControl()
{

}
