#ifndef _EXECUTOR_H
#define _EXECUTOR_H

#include "mpsvr.h"

typedef struct oExecutor{
    void (*executor)(Task *task, Control *iSubgroup);
    Task *task;
}MPExecutor;

void executor(struct MPServer *mpsvr);

#endif
