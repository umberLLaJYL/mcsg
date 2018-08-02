#include "mpsvr.h"

/**
 * main frame of mpsvr.
 */
int main(int argc, char *argv[])
{
    MPServer *mpserver = new (MPServer);
    MPDevice *device = new (MPDevice);
    MPOperater *operater = new (MPOperater, MPSVR_CONF);

    device->operate(device);
    mpserver->server(mpserver, executor->task);
    operater->operate(operater, executor->task);

    delete(MPExecutor, executor);
    delete(MPOperater, operater);
    delete(MPServer, mpserver);

    return 0;
}
