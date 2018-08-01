#include "../../library/mplib/mplib.h"



static void (*deviceInitialize(Device *__restrict device))(Task *)
{
    void (*executor)(Task *);


    return executor;
}

static int mpsvrConfigure(Mpsvr *__restrict mpsvr)
{
    FILE *confFile;
    char optionLine[MP_MAXLINE];

    if(mpLockPossess("/var/run/mpsvr.pid"))
        mpQuit(1, "mpsvr already running\n");

    memset(mpsvr, 0, sizeof(Mpsvr));

    if((confFile = fopen("/etc/mpsvr.conf", "r")) < 0)
        mpExit("mpsvr: can not open '/etc/mpsvr.conf'");
    while(fgets(optionLine, sizeof(optionLine), confFile) != NULL){
        if(strncmp(optionLine, "$Model", 6)){
            
        }
    }
    return 0;
}
