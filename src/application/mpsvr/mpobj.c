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

extern Mpsvr *MpsvrCreate(Mpsvr *__restrict impsvr)
{
    Mpsvr *mpsvr = impsvr;

    if(impsvr == NULL)
        return NULL;

    impsvr->server = integrated;

    if((impsvr->task = (Task *)malloc(sizeof(Task))) == NULL)
        return NULL;

    return mpsvr;
}

extern Device *DeviceCreate(Subgroup *__restrict idevice)
{
    Device *device = idevice;

    if(isubgroup == NULL)
        return NULL;

    if((isubgroup->list = (Control *)malloc(sizeof(Control))) == NULL)
        return NULL;

    isubgroup->operate = obpOperate;

    isubgroup->list->next = NULL;
        
    return subgroup;
}

extern void SubgroupDelete(Subgroup *__restrict isubgroup)
{
    if(isubgroup == NULL)
        return;

    if(isubgroup->list != NULL)
        free(isubgroup->list);

    return;
}
