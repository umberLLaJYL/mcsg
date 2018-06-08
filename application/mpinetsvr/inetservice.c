#include "../../src/mplib/mpmod.h"
#include "../../src/mpmsg.h"
#include "../mpser/mpser.h"
#include "../daemon/mplog.h"

int main(int argc, char *argv[])
{
    _FD clientFD, localClientFD;
    fd_set readSet;
    int hashSum, messageLen, fdFlag, maxFD;
    char message[MP_MAXLINE], reply[MP_MAXLINE];
    struct timeval waitTime;
    struct sockaddr_un localClientAddress;
    struct msgln msg;
    
    clientFD = atoi(argv[1]);
    if((fdFlag = fcntl(clientFD, F_GETFL, 0)) < 0)
        return -1;
    if(fcntl(clientFD, F_SETFL, fdFlag|O_NONBLOCK) < 0)
        return -1;
    mpOpenLog("MCSG", 0, 7);

    memset(&msg, 0, sizeof(msg));
    waitTime.tv_sec = 15;
    waitTime.tv_usec = 0;
    FD_ZERO(&readSet);
    FD_SET(clientFD, &readSet);
    if(select(clientFD+1, &readSet, NULL, NULL, &waitTime) == 0)
        mpQuit(1, "mpinetsvr connection '%s' error: sync timeout\n", argv[2]);
    if((messageLen = mpRead(clientFD, message, sizeof(message))) <= 0)
        mpQuit(1, "mpinetsvr connection '%s' error: no acknowledge\n", argv[2]);
    MurmurHash3_x86_32(message, strlen(message), MP_MSGSEED, &hashSum);
    if(hashSum != MSG_SYNC)
        mpQuit(1, "mpinetsvr connection '%s' error: unknow client\n", argv[2]);
    mpLog(LOG_INFO, "establish connection with '%s'", argv[2]);

    mpGenerateMessage(message, "ack");
    if(mpWrite(clientFD, message, sizeof(message)) < 0)
        mpQuit(1, "mpinetsvr can not sync with server\n");

    if((localClientFD = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1)
        mpExit("mpinetsvr local socket error");

    memset(&localClientAddress, 0, sizeof(localClientAddress));
    localClientAddress.sun_family = AF_LOCAL;
    strcpy(localClientAddress.sun_path, MP_LOCALSVRDIR);
    
    if(connect(localClientFD, (struct sockaddr *)&localClientAddress, sizeof(localClientAddress)))
        mpExit("mpinetsvr can not connect to local server");
    FD_SET(localClientFD, &readSet);

    maxFD = (localClientFD>clientFD?localClientFD:clientFD)+1;
    for(;;){
        if(select(maxFD, &readSet, NULL, NULL, NULL) < 0){
            if(errno == EINTR)
                continue;
            else
                return ESELECT;
        }
        if(FD_ISSET(clientFD, &readSet)){
            if((messageLen = mpRead(clientFD, message, sizeof(message))) == 0){
                mpLog(LOG_INFO, "disconnect with '%s'", argv[2]);
                exit(0);
            }

            /**/

            if((msg.ml_lbrace == msg.ml_rbrace) && (msg.ml_flag == 0)){
                if((messageLen = mpWrite(localClientFD, message, sizeof(message))) <= 0)
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
        }
    }
}
