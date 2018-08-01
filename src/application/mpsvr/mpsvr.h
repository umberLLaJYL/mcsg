#ifndef _MPSVR_H
#define _MPSVR_H

#include "executor.h"
#include "../../library/mplib/mplib.h"

#define mcsgVersion "v1.03.10014"

#define MPSVR_CONF "/etc/mpsvr.conf"

typedef struct oServer{
    void (*server)(struct oServer *mpserver, Task *iTask);
    char version[16];
}MPServer;

#endif
