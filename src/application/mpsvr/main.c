#include "mpsvr.h"

int main(int argc, char *argv[])
{
    MPsvr *mpsvr = new (MPsvr);
    Control *subgroup = new (Control, MPSVR_CONF);
    Task *task = new (Task);

    mpsvr->subgroup = subgroup;
    mpsvr->task = task;

    mpsvr->server(mpsvr);
    mpsvr->operater(mpsvr);
    mpsvr->executor(mpsvr);

    delete(Control, subgroup);
    delete(Task, task);
    delete(Mpsvr, mpsvr);

    return 0;
}
