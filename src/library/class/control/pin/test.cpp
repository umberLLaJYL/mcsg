#include "pincontroller.h"

int main(int argc, char const *argv[])
{
    PinDirectionController *pdc = new PinDirectionController(66);

    PinController pc;

    Pin pin(66);

    pin.bind(pdc);

    delete pdc;

    return 0;
}
