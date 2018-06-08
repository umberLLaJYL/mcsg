#include "../../src/mplib/mpmod.h"
#include "../../src/mpmsg.h"
#include "../mpser/mpser.h"
#include "../daemon/mplog.h"

int main(int argc, char *argv[])
{
    _FD clientFD, localClientFD;
    int hashSum, len, fdFlag;
    char data[MP_MAXLINE], reply[MP_MAXLINE];
    struct timeval waitTime;
    struct sockaddr_un localClientAddress;
    fd_set readSet;
    
    clientFD = atoi(argv[0]);

    if((fdFlag = fcntl(clientFD, F_GETFL, 0)) < 0)
        return -1;
    if(fcntl(clientFD, F_SETFL, fdFlag|O_NONBLOCK) < 0)
        return -1;

    waitTime.tv_sec = 15;
    waitTime.tv_usec = 0;
    FD_ZERO(&readSet);
    FD_SET(clientFD, &readSet);

    if(select(clientFD+1, &readSet, NULL, NULL, &waitTime) == 0)
        mpQuit(1, "mpinetsvr connection '%s:%s' error: sync timeout\n", argv[1], argv[2]);
    if((len = mpRead(clientFD, data, sizeof(data))) < 0)
        mpQuit(1, "mpinetsvr connection '%s:%s' error: no acknowledge\n", argv[1], argv[2]);
    MurmurHash3_x86_32(data, strlen(data), MP_MSGSEED, &hashSum);
    if(hashSum != MSG_SYNC)
        mpQuit(1, "mpinetsvr connection '%s:%s' error: unknow client\n", argv[1], argv[2]);

    mpGenerateMessage(data, "ack");
    if(mpWrite(clientFD, data, sizeof(data)) < 0)
        mpQuit(1, "mpinetsvr can not sync with server\n");

    mpOpenLog("MCSG", 0, 7);
    if((localClientFD = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1)
        mpExit("mpinetsvr local socket error");

    memset(&localClientAddress, 0, sizeof(localClientAddress));
    localClientAddress.sun_family = AF_LOCAL;
    strcpy(localClientAddress.sun_path, MP_LOCALSVRDIR);
    
    if(connect(localClientFD, (struct sockaddr *)&localClientAddress, sizeof(localClientAddress)))
        mpExit("mpinetsvr can not connect to local server");
    mpLog(LOG_INFO, "establish connection with '%s:%s'", argv[1], argv[2]);

    for(;;){
        if(select(clientFD+1, &readSet, NULL, NULL, NULL) < 0){
            if(errno == EINTR)
                continue;
            else
                return ESELECT;
        }
        if((len = mpRead(clientFD, data, sizeof(data))) == 0){
            mpLog(LOG_INFO, "disconnect with '%s:%s'", argv[1], argv[2]);
            exit(0);
        }
        // printf("TCP rcv data: %s\n", data);

        if((len = mpWrite(localClientFD, data, sizeof(data))) <= 0)
            printf("write to local server fial\n");
    }
}
