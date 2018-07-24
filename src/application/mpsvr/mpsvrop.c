#include "mpsvrop.h"

static int systemInitialize(struct MPSVRATTR *__restrict option)
{
    /* io map */
}

// static int plugInitialize(struct MPSVR *mpsvr)
// {

// }

// static fswAction(struct MPSVR *__restrict mpsvr, char *command)
// {

// }

// static int plugServer(const void const *svrfd, void *__restrict args)
// {

// }

static int overallServer(struct MPSVR *__restrict mpsvr)
{
    _FD server, client[16];
    fd_set readSet, grpSet;
    int idx, maxFD, clientFD, numReady, fdFlag, dataLen;
    char data[MP_MAXLINE];
    struct sockaddr_in clientAddress;
    socklen_t socketLen;

    FILE *confFile;
    char optionLine[MP_MAXLINE];
    struct sockaddr_un serverAddress;

    memset(&serverAddress, 0, sizeof(serverAddress));

    if((confFile = fopen("/etc/mpsvr.conf", "r")) < 0)
        mpExit("mpsvr: can not open '/etc/mpsvr.conf'");
    while(fgets(optionLine, sizeof(optionLine), confFile) != NULL){
        if(strncmp(optionLine, "$Model", 6)){
            
        }
    }

    if((server = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
        return ESVRSOCK;

    unlink("/tmp/mcsg/local.socket");
    serverAddress.sun_family = AF_LOCAL;
    strcpy(serverAddress.sun_path, "/tmp/mcsg/local.socket");

    if(bind(server, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_un)))
        return ESVRBIND;
    if(listen(server, MP_BACKLOG))
        return ESVRLISTEN;
    
    maxFD = server+1;
    FD_ZERO(&grpSet);
    FD_SET(server, &grpSet);

    if((fdFlag = fcntl(server, F_GETFL, 0)) < 0)
        return ESVRSOCKOPT;
    if(fcntl(server, F_SETFL, fdFlag|O_NONBLOCK) < 0)
        return ESVRSOCKOPT;

    for(;;){
        readSet = grpSet;
        if((numReady = select(maxFD, &readSet, NULL, NULL, NULL)) < 0){
            if(errno == EINTR)
                continue;
            else
                return ESELECT;
        }
        if(FD_ISSET(server, &readSet)){
            socketLen = sizeof(clientAddress);
            if((clientFD = accept(server, (struct sockaddr *)&clientAddress, &socketLen)) < 0){
                if((errno == EINTR)
#ifdef EWOULDBLOCK
                    || (errno == EWOULDBLOCK)
#endif
#ifdef EPROTO
                    || (errno == EPROTO)
#endif
                )
                    continue;
                else
                    return ESVRWAIT;
            }
            for(idx=0; idx<MP_MAXCLIENT; idx++){
                if(client[idx] == 0){
                    client[idx] = clientFD;
                    break;
                }
            }
            if(idx == MP_MAXCLIENT){
                client[idx] = 0;
                close(clientFD);
                continue;
            }
            FD_SET(clientFD, &grpSet);
            maxFD = (clientFD>maxFD?clientFD:maxFD)+1;

            if(--numReady <= 0)
                continue;
        }
        for(idx=0; idx<(maxFD+1); idx++){
            if(client[idx] == 0)
                continue;
            if(FD_ISSET(client[idx], &readSet)){
                if((dataLen = mpRead(client[idx], data, sizeof(data))) > 0)
                    mpsvr->operate.parser(data, NULL);
                else if(dataLen <= 0){
                    close(client[idx]);
                    FD_CLR(client[idx], &grpSet);
                    client[idx] = 0;
                    printf("disconnect form client%02d\n", idx);                    
                }
                if(--numReady <= 0)
                    break;                
            }
        }
    }
}

extern int mpsvrConfigure(MPSVR *__restrict mpsvr)
{
    FILE *confFile;
    char optionLine[MP_MAXLINE];
    struct sockaddr_un serverAddress;

    memset(mpsvr, 0, sizeof(struct MPSVR));
    memset(&serverAddress, 0, sizeof(serverAddress));

    if((confFile = fopen("/etc/mpsvr.conf", "r")) < 0)
        mpExit("mpsvr: can not open '/etc/mpsvr.conf'");
    while(fgets(optionLine, sizeof(optionLine), confFile) != NULL){
        if(strncmp(optionLine, "$Model", 6)){
            
        }
    }
    return 0;
}
