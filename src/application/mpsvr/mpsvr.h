#ifndef _MPSVR_H
#define _MPSVR_H

#include "executor.h"
#include "../../library/mplib/mplib.h"

#define mcsgVersion "v1.05.10014"

#define MPSVR_CONF "/etc/mpsvr.conf"

typedef struct Server{

    void (*initialize)(struct Server *mpserver);
    void (*start)(struct Server *mpserver);

    _FD file;
    char version[16];

    struct cli{
        _FD file;
        int status;
    }client;

    struct manager{
        void (*issue)(const char *message, Task *task);

        Task *task;
    }manager;

}MPServer;

#endif
