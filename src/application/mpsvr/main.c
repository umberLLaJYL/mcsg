#include "mpsvr.h"

/**
 * main frame of mpsvr.
 */
int main(int argc, char *argv[])
{
    MPServer *mpserver = new (MPServer);
    MPDevice *device = new (MPDevice);
    Operater *operater = new (Operater, MPSVR_CONF);
    Task *task = new (Task);

    device->operater = operater;
    operater->task = mpserver->task = task;

    device->construct(device, MPSVR_CONF);

    mpserver->initialize(mpserver);
    mpserver->start(mpserver);

    delete(MPDevice, device);
    delete(MPServer, mpserver);
    delete(Operater, operater);
    delete(Task, task);

    return 0;
}
