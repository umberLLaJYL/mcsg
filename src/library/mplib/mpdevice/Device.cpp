#include "Device.h"

using namespace std;

Device::Device(const string &conf) : Device()
{
    char buf[4096];
    ifstream confFile("test.json", ios::in);

    confFile.read(buf, sizeof(buf));
    this->information = buf;

    cout << "device has been created: " << conf << endl;
}

Device::~Device()
{
    cout << "device has been deleted" << endl;
}


const string &Device::getInformation() const
{
    return this->information;
}

const string &Device::getStatus() const
{
    return this->status;
}

void Device::pinInitialize() const
{
    fstream iomap("test.json", ios::in);

    // iomap.read
}
