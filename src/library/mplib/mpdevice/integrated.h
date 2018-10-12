#ifndef _INTEGRATED_H
#define _INTEGRATED_H

#include "../mpcontrol/control.h"

class Integrated {

private:
    std::size_t countAbnormality;
    std::size_t runtime;

    std::string information;
    std::string status;

    std::map<std::string, GPIO> pin;
    std::map<std::string, IoControl> ioControlGroup;

    void _initialize(const std::string &conf) {
        std::ifstream configFile(conf);
        std::string line;
        std::string file;
        rapidjson::Document device;

        while(std::getline(configFile, line))
            file += line;
        configFile.close();

        device.Parse(file.c_str());

        for(auto &idx : device["pin"].GetObject())
            this->pin.insert({idx.name.GetString(), GPIO(idx.value.GetArray()[0].GetInt(), idx.value.GetArray()[1].GetString())});
        
        for(auto &type : device["subgroup"].GetObject()) {
            if(type.value.GetArray().Size() != 0) {
                this->ioControlGroup.insert({type.value.GetArray()[0].GetString(), IoControl(type.value.GetArray()[0].GetString())});
            }
        }
    }
    
public:
    Integrated() = default;
    Integrated(const std::string &conf) {
        this->_initialize(conf);
    }
    ~Integrated();

    // const string &getInformation() const;
    // const string &getStatus() const;

    bool isChange() const;

    virtual void start() = 0;

protected:
    void pinInitialize();

    virtual void operate() = 0;
    virtual void analyse() = 0;
};

#endif
