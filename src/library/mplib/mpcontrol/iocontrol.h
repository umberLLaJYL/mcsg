#ifndef _IOCONTROL_H
#define _IOCONTROL_H

#include "control.h"

class IoControl {

private:
    unsigned int pinNum;
    std::string alias;

    std::vector<GPIO> pin;
    std::map<std::string, int> sequence;
    std::map<std::string, std::pair<int, int>> parameter;

    void _updata() {

    }

    bool _setPinValue(int pinSelect, int vlu) {
        if((pinSelect < 1) || (pinSelect > this->pinNum))
            return false;
        return this->pin[pinSelect].setValue(vlu);
    }

    int _getPinValue(int pinSelect) {
        if((pinSelect < 1) || (pinSelect > this->pinNum))
            return -1;
        return this->pin[pinSelect].getValue();
    }

public:
    IoControl(const std::string &prefix) : pinNum(0), alias(prefix) {
        std::ifstream configFile(prefix+".json");
        std::string line;
        std::string file;
        rapidjson::Document ioCtrl;
        
        while(std::getline(configFile, line))
            file += line;
        
        configFile.close();

        ioCtrl.Parse(file.c_str());

        for(rapidjson::SizeType cnt = 0; cnt != ioCtrl["pin"].Size(); ++cnt)
            this->pin.push_back(GPIO());

        for(rapidjson::SizeType cnt = 0; cnt != ioCtrl["pin"].Size(); ++cnt)
            this->pin[cnt].reexport(ioCtrl["pin"][cnt].GetInt(), ioCtrl["dir"][cnt].GetString());

        this->pinNum = this->pin.size();

        for(auto &seq : ioCtrl["sequence"].GetObject())
            this->sequence.insert({seq.name.GetString(), seq.value.GetInt()});

        for(auto &parm : ioCtrl["parameter"].GetObject())
            this->parameter.insert({parm.name.GetString(), {parm.value.GetInt(), 0}});

        for(std::map<std::string, std::pair<int, int>>::iterator element = this->parameter.begin();
            element != this->parameter.end();
            ++element) {
            
        }
    }

    ~IoControl() {
        this->pin.clear();
        this->sequence.clear();
        this->parameter.clear();
    }
    
    // bool operator == (int);
    // bool operator != (int);
    // GPIO &operator [] (int);

    void reinitialize(const std::string &prefix) {
        std::ifstream configFile(prefix+".json");
        std::string line;
        std::string file;
        rapidjson::Document ioCtrl;

        while(std::getline(configFile, line))
            file += line;
        
        configFile.close();

        ioCtrl.Parse(file.c_str());

        for(rapidjson::SizeType cnt = 0; cnt != ioCtrl["pin"].Size(); ++cnt)
            this->pin.push_back(GPIO());

        for(rapidjson::SizeType cnt = 0; cnt != ioCtrl["pin"].Size(); ++cnt)
            this->pin[cnt].reexport(ioCtrl["pin"][cnt].GetInt(), ioCtrl["dir"][cnt].GetString());

        this->pinNum = this->pin.size();
        this->alias = prefix;

        for(auto &seq : ioCtrl["sequence"].GetObject())
            this->sequence.insert({seq.name.GetString(), seq.value.GetInt()});
    }

    void deinitialize() {
        this->pinNum = 0;
        this->pin.clear();
        this->sequence.clear();
        this->parameter.clear();
    }

    bool execute(const std::string &order) {
        std::map<std::string, int>::iterator element;

        if((element = this->sequence.find(order)) == this->sequence.end())
            return false;
            
#ifdef MP_BIG_ENDIAN
        for(int num = 0; num != this->pinNum; ++num)
            this->pin[num].setValue(((element->second) >> num) & 0x01);
#endif
#ifdef MP_LITTLE_ENDIAN
        for(int num = 0; num != this->pinNum; ++num)
            this->pin[num].setValue(((element->second) << num) & 0x01);
#endif
        return true;
    }

    bool setDirection(int pinSelect, const char *dir) {
        if((pinSelect < 1) || (pinSelect > this->pinNum))
            return false;
        return this->pin[pinSelect].setDirection(dir);
    }

    bool setPinValue(int pinSelect, int vlu) {
        return this->_setPinValue(pinSelect, vlu);
    }

    int updata(const std::string name) {
        // return this->_updata();
    }

    int getPinValue(int pinSelect) {
        return this->_getPinValue(pinSelect);
    }
};

#endif
