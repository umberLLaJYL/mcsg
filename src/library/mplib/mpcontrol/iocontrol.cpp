#include <fstream>

#include "control.h"

IoControl::IoControl(const std::string &dir) : pinStat(-1)
{
    std::ifstream configFile(dir);
    std::string line;
    std::string file;
    rapidjson::Document ioctrl;

    while(std::getline(configFile, line))
        file += line;
    
    configFile.close();

    ioctrl.Parse(file.c_str());

    for(rapidjson::SizeType cnt = 0; cnt != ioctrl["pin"].Size(); ++cnt)
        this->pin.push_back(GPIO());

    for(rapidjson::SizeType cnt = 0; cnt != ioctrl["pin"].Size(); ++cnt)
        this->pin[cnt].reexport(ioctrl["pin"][cnt].GetInt(), ioctrl["dir"][cnt].GetString());

    for(auto &seq : ioctrl["sequence"].GetObject())
        this->sequence.insert({seq.name.GetString(), seq.value.GetInt()});
}

IoControl::~IoControl()
{
    this->pin.clear();
    this->sequence.clear();
}

bool IoControl::execute(const std::string &order)
{
    std::map<std::string, int>::iterator element;
    int seq;

    if((element = this->sequence.find(order)) == this->sequence.end())
        return false;
    
    seq = element->second;
    
    for(size_t num = 0; num != this->pin.size(); ++num){

    }
}

int IoControl::getStatus()
{
    return this->pinStat;
}

int IoControl::getStatus(std::size_t pinSelect)
{

}
