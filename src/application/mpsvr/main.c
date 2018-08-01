#include "mpsvr.h"

/**
 * main frame of mpsvr.
 */
int main(int argc, char *argv[])
{
    MPServer *mpserver = new (MPServer);
    MPDevice *device = new (MPDevice, MPSVR_CONF);
    MPExecutor *executor = new (MPExecutor);

    mpserver->server(mpserver, executor->task);
    device->operater(device, executor->task);
    executor->executor(executor, device->subgroup);

    delete(MPExecutor, executor);
    delete(MPDevice, device);
    delete(MPServer, mpserver);

    return 0;
}
