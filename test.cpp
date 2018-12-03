#include "factory/ResourceFactory/GPIOFactory/GPIOFactory.h"
#include "class/ResourceController/GPIOController/GPIOController.h"

// #include "../../json/rapidjson/document.h"

// using namespace rapidjson;

GPIOFactory gpioFactory;
GPIOController gpioController;

int main(int argc, char *argv[])
{
    gpioController.addResource(gpioFactory.create("66"));

    MrcDevice.addController(ControllerFactory.create("fsw2.json"));

    if(MrcDevice("pd1") < -30.00)
        MrcDevice.controller("fsw1").execute("<BP01_S_1>");

    return 0;
}
