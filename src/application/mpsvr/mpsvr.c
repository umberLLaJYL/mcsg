#include "mpsvr.h"

static int integrated(struct MPServer *mpsvr)
{
    _FD server, clientFD, client[16];
    fd_set readSet, grpSet;
    int idx, maxFD, numReady, fdFlag;
    char data[MP_MAXLINE];
    struct sockaddr_un serverAddress;

    if((server = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
        return ESVRSOCK;

    memset(&serverAddress, 0, sizeof(serverAddress));
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
            if((clientFD = accept(server, (struct sockaddr *)NULL, NULL)) < 0){
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
                if(mpRead(client[idx], data, sizeof(data)) > 0)
                {/* fill task */}
                else{
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

/**
 * Construct object MPServer.
 */
extern MPServer *MPServerConstruct(MPServer *__restrict iMPServer)
{
    MPServer *mpServer = iMPServer;

    if(mpServer == NULL)
        return NULL;

    memset(mpServer, 0, sizeof(MPServer));
    mpServer->server = integrated;
    strncpy(mpServer->version, mcsgVersion, 11);

    return mpServer;
}

extern void MPServerDestruct(MPServer *__restrict iMPServer)
{
    if(iMPServer == NULL)
        return;

    return;
}
