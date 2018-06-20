#include "mpsvr.h"

// static struct taskln *mpGenerateTaskQueue(void)
// {
//     struct taskln *head;

//     if((head = (struct taskln *)malloc(sizeof(struct taskln))) == NULL)
//         return NULL;
//     head->t_next = NULL;

//     return head;
// }

// static struct msgln *mpAssignTask(struct taskln *list, const char *msg)
// {
//     unsigned int lnid = 0;
//     struct taskln *node, *tail;
    
//     node = list;
//     while(node->t_next){
//         lnid++;
//         node = node->t_next;
//     }
//     if((tail = (struct taskln *)malloc(sizeof(struct taskln))) == NULL)
//         return NULL;

//     tail->ml_lnid = lnid;
    
//     tail->ml_next = NULL;
//     node->ml_next = tail;

//     memcpy(tail->ml_buf, msg, MP_MAXLINE);
// }

static int pollingServer(const void const *svrfd, void *__restrict args)
{
    _FD ttyFD, clientFD, client[MP_MAXCLIENT];
    fd_set readSet, grpSet;
    int idx, maxFD, serverFD, numReady, fdFlag, dataLen;
    char data[MP_MAXLINE];
    struct sockaddr_in clientAddress;
    struct timeval tick;
    socklen_t socketLen;
    
    /* initialize mpsvrFD */
    ttyFD = *(_FD *)args;
    maxFD = serverFD = *(_FD *)svrfd;
    FD_ZERO(&grpSet);
    FD_SET(serverFD, &grpSet);
    for(idx=0; idx<MP_MAXCLIENT; idx++)
        client[idx] = -1;

    if((fdFlag = fcntl(serverFD, F_GETFL, 0)) < 0)
        return ESVRSOCKOPT;
    if(fcntl(serverFD, F_SETFL, fdFlag|O_NONBLOCK) < 0)
        return ESVRSOCKOPT;
    tick.tv_sec = 1;
    tick.tv_usec = 0;
    for(;;){
        readSet = grpSet;
        if((numReady = select(maxFD+1, &readSet, NULL, NULL, NULL)) < 0){
            if(errno == EINTR)
                continue;
            else
                return ESELECT;
        }else if(numReady == 0){
            tick.tv_sec = 1;
            tick.tv_usec = 0;
            // for(){
                
            // }
            continue;
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
                if(client[idx] == -1){
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
        // if(FD_ISSET(ttyFD, &readSet)){

        //     if(--numReady <= 0)
        //         continue;
        // }
        for(idx=0; idx<(maxFD+1); idx++){
            if(client[idx] == -1)
                continue;
            if(FD_ISSET(client[idx], &readSet)){
                if((dataLen = mpRead(client[idx], data, sizeof(data))) > 0){

                    /* parse */

                    if(mpWrite(client[idx], data, sizeof(data)) <= 0)
                        printf("write to local server fial\n");   
                }else if(dataLen == 0){
                    close(client[idx]);
                    FD_CLR(client[idx], &grpSet);
                    client[idx] = -1;
                    printf("disconnect form client%02d\n", idx);                    
                }else{

                }
                if(--numReady <= 0)
                    break;                
            }
        }
    }
}

void *cothread(void *args)
{
    struct taskln *task;

    sleep(1);

    task = (struct taskln*)args;

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    _FD localServerFD, ttyFD;
    int errorCode;
    struct svropt_local serverOprion;
    pthread_t cothreadID;

    if(mpLockPossess("/var/run/mpser.pid"))
        mpExit("mpser is already running");

    if(ttyFD = (uartInitialize("/dev/ttySP0", 115200, 8, 'n', 1)) < 0)
        mpExit("mpser can not open 'ttySP0'");

    strncpy(serverOprion.sol_parh, MP_LOCALSVRDIR, sizeof(MP_LOCALSVRDIR));
    if((errorCode = mpServerInitialize(AF_LOCAL, SOCK_STREAM, &serverOprion)) < 0)
        mpExit("mpser initialize server fail: %d", errorCode);

    // if((errorCode = pthread_create(&cothreadID, NULL, cothread, NULL)) != 0)
    //     mpExit("mpser initialize co-thread fail: %d", errorCode);

    if((errorCode = mpServerStart(&serverOprion.sol_svrfd, &ttyFD, pollingServer)) < 0)
        mpQuit(errorCode, "mpser shutdown unexpected: %d\n", errorCode);
}
