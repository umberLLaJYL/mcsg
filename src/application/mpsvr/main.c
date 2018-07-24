#include "mpsvr.h"

int main(int argc, char *argv[])
{
    MPsvr *mpsvr = new (MPsvr);
    Control *subgroup = new (Control, MPSVR_CONF);
    Task *task = new (Task);

    mpsvr->subgroup = subgroup;
    mpsvr->task = task;

    mpsvr->server(mpsvr->task);
    mpsvr->operater(mpsvr->subgroup);
    mpsvr->executor(mpsvr->subgroup, mpsvr->task);

    delete(Control, subgroup);
    delete(Task, task);
    delete(Mpsvr, mpsvr);

    return 0;
}
