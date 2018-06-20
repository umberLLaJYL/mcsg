#include "../../src/mplib/mpmod.h"
#include "../../src/mpmsg.h"
#include "../mpsvr/mpsvr.h"
#include "../daemon/mplog.h"

int main(int argc, char *argv[])
{
    _FD clientFD, localClientFD;
    fd_set readSet;
    int hashSum, messageLen, fdFlag, maxFD;
    char reply[MP_MAXLINE];
    struct timeval waitTime;
    struct sockaddr_un localClientAddress;
    struct msgln message;
    
    clientFD = atoi(argv[1]);
    // if((fdFlag = fcntl(clientFD, F_GETFL, 0)) < 0)
    //     return -1;
    // if(fcntl(clientFD, F_SETFL, fdFlag|O_NONBLOCK) < 0)
    //     return -1;
    mpOpenLog("MCSG", 0, 7);

    memset(&message, 0, sizeof(message));
    waitTime.tv_sec = 15;
    waitTime.tv_usec = 0;
    FD_ZERO(&readSet);
    FD_SET(clientFD, &readSet);
    if(select(clientFD+1, &readSet, NULL, NULL, &waitTime) == 0)
        mpQuit(1, "mpinetsvr connection '%s' error: sync timeout\n", argv[2]);
    if((messageLen = mpRead(clientFD, message.ml_buf, sizeof(message.ml_buf))) <= 0)
        mpQuit(1, "mpinetsvr connection '%s' error: no acknowledge\n", argv[2]);
    MurmurHash3_x86_32(message.ml_buf, strlen(message.ml_buf), MP_MSGSEED, &hashSum);
    if(hashSum != MSG_SYNC)
        mpQuit(1, "mpinetsvr connection '%s' error: unknow client\n", argv[2]);
    mpLog(LOG_INFO, "establish connection with '%s'", argv[2]);

    mpGenerateMessage(message.ml_buf, "ack");
    if(mpWrite(clientFD, message.ml_buf, sizeof(message.ml_buf)) < 0)
        mpQuit(1, "mpinetsvr can not sync with server\n");

    if((localClientFD = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1)
        mpExit("mpinetsvr local socket error");

    memset(&localClientAddress, 0, sizeof(localClientAddress));
    localClientAddress.sun_family = AF_LOCAL;
    strcpy(localClientAddress.sun_path, MP_LOCALSVRDIR);
    
    if(connect(localClientFD, (struct sockaddr *)&localClientAddress, sizeof(localClientAddress)))
        mpExit("inetser can not connect to local server");

    maxFD = (localClientFD>clientFD?localClientFD:clientFD)+1;
    for(;;){
        FD_SET(localClientFD, &readSet);
        FD_SET(clientFD, &readSet);
        if(select(maxFD, &readSet, NULL, NULL, NULL) < 0){
            if(errno == EINTR)
                continue;
            else
                return ESELECT;
        }
        if(FD_ISSET(clientFD, &readSet)){
            if((messageLen = mpRead(clientFD, message.ml_buf, sizeof(message.ml_buf))) == 0){
                mpLog(LOG_INFO, "disconnect with '%s'", argv[2]);
                exit(0);
            }

            printf("tcp rcv: %s\n", message.ml_buf);

            /* process */

            if((message.ml_lbrace == message.ml_rbrace) && (message.ml_flag == 0)){
                if((messageLen = mpWrite(localClientFD, message.ml_buf, sizeof(message.ml_buf))) <= 0)
                    printf("write to local server fial\n");     
            }
        }
        if(FD_ISSET(localClientFD, &readSet)){
            if((messageLen = mpRead(localClientFD, reply, sizeof(reply))) == 0){
                mpLog(LOG_INFO, "disconnect with '%s'", argv[2]);
                exit(0);
            }
            if((messageLen = mpWrite(clientFD, reply, sizeof(reply))) <= 0)
                printf("write to local server fial\n");
            printf("mpsvr reply\n");
        }
    }
}
