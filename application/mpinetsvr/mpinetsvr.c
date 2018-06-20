#include "../../src/mplib/mpmod.h"
#include "../../src/mpmsg.h"
#include "../mpsvr/mpsvr.h"
#include "../daemon/mplog.h"

struct svrargs{
    char sa_dir[104];
    _FD sa_lfd;
};

void clearUp(int singo)
{
    wait(NULL);
}

static void optionInitialize(int argc, char *argv[], struct svropt_inet *__restrict serverOption)
{
    int opt;
    _PORT port0, port1;
    static struct option options[] = {
        {"default", optional_argument, NULL, 'd'},
        {"tcponly", optional_argument, NULL, 't'},
        {"udponly", optional_argument, NULL, 'u'}
    };
    
    memset(serverOption, 0, sizeof(struct svropt_inet));
    while((opt = getopt_long(argc, argv, "v?", options, NULL)) != -1){
        switch(opt){
            case 'v':{
                
                break;
            }
            case 'd':{
                serverOption->soi_mode = MP_INET_DFLT;
                serverOption->soi_tcpport = atoi(optarg);
                serverOption->soi_udpport = atoi(argv[optind]);
                if((serverOption->soi_tcpport < 1024) || (serverOption->soi_udpport < 1024))
                    mpQuit(1, "mpinetsvr: invalid port\n");
                break;
            }
            case 't':{
                serverOption->soi_mode = MP_INET_TCPONLY;
                serverOption->soi_tcpport = atoi(optarg);
                if(serverOption->soi_tcpport < 1024)
                    mpQuit(1, "mpinetsvr: invalid port\n");
                break;
            }
            case 'u':{
                serverOption->soi_mode = MP_INET_UDPONLY;
                serverOption->soi_tcpport = atoi(optarg);
                if(serverOption->soi_udpport < 1024)
                    mpQuit(1, "mpinetsvr: invalid port\n");
                break;
            }
            case '?':
            default: printf("Usage: \n");exit(0);
        }
    }
}

static int mixServer(const struct svropt_inet const *option, const struct svrargs *__restrict args)
{
    _FD clientFD, maxFD;
    fd_set readSet;
    pid_t clientPID;
    char ip[INET_ADDRSTRLEN], peerAddr[INET_ADDRSTRLEN+10], tcpClientFDInChar[10];
    char mpsvrBuffer[MP_MAXLINE], udpBuffer[MP_MAXLINE];
    struct sockaddr_in tcpClientAddress, udpClientAddress;
    socklen_t socketLen;

    maxFD = option->soi_tcpfd>option->soi_udpfd?option->soi_tcpfd:option->soi_udpfd;
    maxFD = (maxFD>args->sa_lfd?maxFD:args->sa_lfd)+1;
    FD_ZERO(&readSet);
    for(;;){
        if(option->soi_tcpfd)
            FD_SET(option->soi_tcpfd, &readSet);
        if(option->soi_udpfd)
            FD_SET(option->soi_udpfd, &readSet);
        // FD_SET(args->sa_lfd, &readSet);

        if(select(maxFD+1, &readSet, NULL, NULL, NULL) < 0){
            if(errno == EINTR)
                continue;
            else
                return ESVRWAIT;
        }
        if(option->soi_mode != MP_INET_UDPONLY){
            if(FD_ISSET(option->soi_tcpfd, &readSet)){
                socketLen = sizeof(tcpClientAddress);
                if((clientFD = accept(option->soi_tcpfd, (struct sockaddr *)&tcpClientAddress, &socketLen)) < 0){
                    if(errno == EINTR)
                        continue;
                    else
                        return ESVRWAIT;
                }
                inet_ntop(AF_INET, &tcpClientAddress.sin_addr, ip, sizeof(ip));
                snprintf(tcpClientFDInChar, sizeof(tcpClientFDInChar), "%d", clientFD);
                snprintf(peerAddr, sizeof(peerAddr), "%s:%d", ip, tcpClientAddress.sin_port);

                if((clientPID = fork()) == 0){
                    close(args->sa_lfd);
                    if(execlp(args->sa_dir, "[inetser]", tcpClientFDInChar, peerAddr, (char *)0))
                        exit(ESVRSER);
                }
                close(clientFD);
                continue;
            }
        }
        if(option->soi_mode != MP_INET_TCPONLY){
            if(FD_ISSET(option->soi_udpfd, &readSet)){
                socketLen = sizeof(udpClientAddress);
                memset(udpBuffer, 0, sizeof(udpBuffer));
                if(recvfrom(option->soi_udpfd, udpBuffer, sizeof(udpBuffer), 0, (struct sockaddr *)&udpClientAddress, &socketLen) < 0){
                    if(errno == EINTR)
                        continue;
                    else
                        return ESVRWAIT;
                }
                // if((msg.ml_lbrace == msg.ml_rbrace) && (msg.ml_flag == 0)){
                    if(mpWrite(args->sa_lfd, udpBuffer, sizeof(udpBuffer)))
                        printf("write to local server fial\n");
                // }
            }
        }
        if(FD_ISSET(args->sa_lfd, &readSet)){
            if(mpRead(args->sa_lfd, mpsvrBuffer, sizeof(mpsvrBuffer))){
                mpLog(LOG_INFO, "disconnect with '%s'");
                exit(0);
            }
            if(sendto(option->soi_udpfd, mpsvrBuffer, sizeof(mpsvrBuffer), 0, (struct sockaddr *)&udpClientAddress, socketLen))
                printf("write to local server fial\n");
        }
    }
}

int main(int argc, char *argv[])
{
    int mode, errorCode;
    struct sockaddr_un localClientAddress;
    struct svropt_inet serverOprion;
    struct svrargs svrArgs;

    if(mpLockPossess("/var/run/mpinetsvr.pid"))
        mpQuit(1, "mpinetsvr is running already\n");

    optionInitialize(argc, argv, &serverOprion);
    mpOpenLog("MCSG", 0, 7);

    serverOprion.soi_procfunc = NULL;
    if((errorCode = mpServerInitialize(AF_INET, SOCK_MIX, &serverOprion)) < 0)
        mpExit("mpinetsvr initialize fail: %d", errorCode);

    if(mpSignal(SIGCHLD, clearUp) == SIG_ERR)
        mpExit("mpinetsvr register handler fail");

    printf("mpinetsvr initialized.\n");
    mpLog(LOG_INFO, "mpinetsvr start");

    if((svrArgs.sa_lfd = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1)
        mpExit("mpsvr local socket error");

    memset(&localClientAddress, 0, sizeof(localClientAddress));
    localClientAddress.sun_family = AF_LOCAL;
    strcpy(localClientAddress.sun_path, MP_LOCALSVRDIR);
    
    if(connect(svrArgs.sa_lfd, (struct sockaddr *)&localClientAddress, sizeof(localClientAddress)))
        mpExit("mpinetsvr can not connect to local server");
    strcpy(svrArgs.sa_dir, "./bin/.inetser");
    if((errorCode = mixServer(&serverOprion, &svrArgs)) < 0)
        mpQuit(1, "mpinetsvr shutdown unexpected: %d\n", errorCode);
}
