#include "../mpobj.h"

using namespace std;

class Cabinet : public Device {

private:
    /* data */
public:
    Cabinet(/* args */);
    ~Cabinet();

    void start() override;

protected:
    void operate() override;
    void analyse() override;

};

Cabinet::Cabinet(/* args */)
{
}

Cabinet::~Cabinet()
{
}

void Cabinet::start()
{
    Cabinet::operate();
}

void Cabinet::operate()
{
}
