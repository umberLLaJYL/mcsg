#include "factory/ResourceFactory/GPIOFactory/GPIOFactory.h"
#include "class/ResourceController/GPIOController/GPIOController.h"

// #include "../../json/rapidjson/document.h"

int main(int argc, char *argv[])
{
    MrcDevice.addController(MrcFactory.create("fsw1"));
    MrcFactory.create("pd1");

    ResourceFactory.create("GPIO", "66");
    ResourceFactory.create("ADC", "adc1");

    ResourceSetterControllerFactory.create("GPIOSetterController");
    ResourceSetterFactory.create("GPIOValueSetter", "66");

    if(MrcDevice("pd1") < -30.00)
        MrcDevice["fsw1"].execute("<BP01_S_1>");

    return 0;
}
