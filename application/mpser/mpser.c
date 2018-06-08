#include "../../src/mpmsg.h"
#include "mpser.h"

static int pollingServer(const void const *svrfd, void *args)
{
    _FD clientFD, client[MP_MAXCLIENT];
    fd_set readSet, grpSet;
    struct sockaddr_in clientAddress;
    int idx, maxFD, serverFD, numReady, fdFlag, dataLen;
    const int clientIdle = -1;
    char data[MP_MAXLINE];
    socklen_t socketLen;

    if(args != (void *)0)
        return 1;
    
    maxFD = serverFD = *(int *)svrfd;
    FD_ZERO(&grpSet);
    FD_SET(serverFD, &grpSet);
    for(idx=0; idx<MP_MAXCLIENT; idx++)
        client[idx] = clientIdle;

    /* configure server into nonblock mode to prevent blocking attack */
    if((fdFlag = fcntl(serverFD, F_GETFL, 0)) < 0)
        return ESVRSOCKOPT;
    if(fcntl(serverFD, F_SETFL, fdFlag|O_NONBLOCK) < 0)
        return ESVRSOCKOPT;

    for(;;){
        readSet = grpSet;
        if((numReady = select(maxFD+1, &readSet, NULL, NULL, NULL)) < 0){
            if(errno == EINTR)
                continue;
            else
                return ESELECT;
        }

        if(FD_ISSET(serverFD, &readSet)){
            socketLen = sizeof(clientAddress);
            if((clientFD = accept(serverFD, (struct sockaddr *)&clientAddress, &socketLen)) < 0){
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
                if(client[idx] == clientIdle){
                    client[idx] = clientFD;
                    break;
                }
            }
            if(idx == MP_MAXCLIENT){
                close(clientFD);
                continue;
            }
            FD_SET(clientFD, &grpSet);
            maxFD = clientFD>maxFD?clientFD:maxFD;

            if(--numReady <= 0)
                continue;
        }
        for(idx=0; idx<(maxFD+1); idx++){
            if(client[idx] == clientIdle)
                continue;
            if(FD_ISSET(client[idx], &readSet)){
                if((dataLen = mpRead(client[idx], data, sizeof(data))) > 0){
                    // printf("local server rcv: %s\n", data);
                }else if(dataLen == 0){
                    close(client[idx]);
                    FD_CLR(client[idx], &grpSet);
                    client[idx] = clientIdle;
                    printf("disconnect form client%02d\n", idx);                    
                }else{

                }
                if(--numReady <= 0)
                    break;                
            }
        }
    }
}

int main(int argc, char *argv[])
{
    _FD localServerFD;
    int errorCode;
    struct svropt_local serverOprion;

    if(mpLockPossess("/var/run/mpser.pid"))
        mpQuit(1, "mpser is already running");

    strncpy(serverOprion.so_parh, MP_LOCALSVRDIR, sizeof(MP_LOCALSVRDIR));
    if((errorCode = mpServerInitialize(AF_LOCAL, SOCK_STREAM, &serverOprion)) < 0)
        mpExit("mpser initialize fail: %d", errorCode);
    if((errorCode = mpServerStart((_FD *)&serverOprion.so_svrfd, (void *)0, pollingServer)) < 0)
        mpQuit(errorCode, "mpser shutdown unexpected: %d\n", errorCode);
}
