#ifndef _IOCONTROL_H
#define _IOCONTROL_H

#include "control.h"

class IoControl {

private:
    unsigned int pinNum;
    std::string alias;

    std::vector<GPIO> pin;
    std::map<std::string, std::vector<int>> sequence;
    std::map<std::string, std::pair<int, int>> parameter;

    bool _initialize(const std::string &prefix) {
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

        for(auto &seq : ioCtrl["sequence"].GetObject()) {
            auto order = this->sequence.insert({seq.name.GetString(), {}});
            for(auto &element: seq.value.GetArray())
                order.first->second.push_back(element.GetInt());
        }

        for(auto &parm : ioCtrl["parameter"].GetObject())
            this->parameter.insert({parm.name.GetString(), {parm.value.GetInt(), 0}});

        this->_updata();
    }

    void _deinitialize() {
        this->pinNum = 0;
        this->pin.clear();
        this->sequence.clear();
        this->parameter.clear();
    }

    void _updata() {
        for(auto &element : this->parameter) {
            element.second.second = 0;
            for(int pinSelect = 0; pinSelect != this->pinNum; ++pinSelect)
                if(element.second.first & (0x01 << pinSelect))
                    element.second.second |= (this->pin[pinSelect].getValue() << pinSelect);
        }
    }

    bool _execute(const std::string &order) {
        std::map<std::string, std::vector<int>>::iterator element;

        if((element = this->sequence.find(order)) == this->sequence.end())
            return false;

        switch(element->second.size()) {
            case 1: {
                for(int pinSelect = 0; pinSelect != this->pinNum; ++pinSelect)
                    this->pin[pinSelect].setValue(element->second[0] & (0x01 << pinSelect));
                break;
            }

            case 3: {
                for(int pinSelect = 0; pinSelect != this->pinNum; ++pinSelect) {
                    if(element->second[0] & (0x01 << pinSelect)) {
                        if(element->second[1] & (0x01 << pinSelect))
                            this->pin[pinSelect].setDirection("out");
                        else
                            this->pin[pinSelect].setDirection("in");
                        this->pin[pinSelect].setValue(element->second[2] & (0x01 << pinSelect));
                    }
                }
                break;
            }

            default: break;
        }    
        this->_updata();
        return true;
    }

    bool _setPinDirection(int pinIdx, const char *dir) {
        if((pinIdx < 1) || (pinIdx > this->pinNum))
            return false;
        return this->pin[pinIdx-1].setDirection(dir);
    }

    bool _setPinValue(int pinIdx, int vlu) {
        if((pinIdx < 1) || (pinIdx > this->pinNum))
            return false;
        return this->pin[pinIdx-1].setValue(vlu);
    }

    int _getParameter(const std::string &parm) {
        std::map<std::string, std::pair<int, int>>::iterator element = this->parameter.find(parm);
        if(element == this->parameter.end())
            return 0xff;
        return element->second.second;
    }

    int _getPinValue(int pinIdx) {
        if((pinIdx < 1) || (pinIdx > this->pinNum))
            return -1;
        return this->pin[pinIdx-1].getValue();
    }

public:
    IoControl(const std::string &prefix) : pinNum(0), alias(prefix) {
        this->_initialize(prefix);
    }

    ~IoControl() {
        this->_deinitialize();
    }

    int operator [] (const std::string parm) {
        return this->getParameter(parm);
    }

    void reinitialize(const std::string &prefix) {
        this->_deinitialize();
        this->_initialize(prefix);
    }

    void deinitialize() {
        this->_deinitialize();
    }

    void updata() {
        this->_updata();
    }

    bool execute(const std::string &order) {
        return this->_execute(order);
    }

    bool setPinDirection(int pinIdx, const char *dir) {
        return this->_setPinDirection(pinIdx, dir);
    }

    bool setPinValue(int pinIdx, int vlu) {
        return this->_setPinValue(pinIdx, vlu);
    }

    int getParameter(const std::string &parm) {
        return this->_getParameter(parm);
    }

    int getPinValue(int pinIdx) {
        return this->_getPinValue(pinIdx);
    }
};

#endif