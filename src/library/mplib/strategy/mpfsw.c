#include "mpfsw.h"

static void fswStrategy(Task *task)
{

}

extern void fswOperate(Task *task)
{
    pthread_t fswOp;

    pthread_create(&fswOp, NULL, fswOperate, NULL);
}
