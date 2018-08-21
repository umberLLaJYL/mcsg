#include "../mpobj.h"

using namespace std;

/**
 * abstract base object: Device.
 */
class Device {

private:
    size_t countControl;
    size_t countAbnormality;

public:
    Device(const string &conf);
    virtual ~Device();

    virtual void operater() = 0;
};

Device::Device(const string &conf)
{
    cout << "device has been created: " << conf << endl;
}

Device::~Device()
{
    cout << "device has been deleted" << endl;
}
