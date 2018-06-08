#include "mpmod.h"

/**********************************************************************/
/* function: initialize local network interface card(NIC).            */
/* input: NIC: NIC that nedd to be initialized.                       */
/* output: error code.                                                */
/**********************************************************************/
static int inetServerInitialize(const int type, struct svropt_inet *__restrict__ serverOption)
{
    int fdFlag, enable = 1;
    struct sockaddr_in serverAddress;

    switch(type){
        case SOCK_DGRAM:
        case SOCK_STREAM:
        case SOCK_RAW:
            break;
        default:
            return ESVRTYPE;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if((serverOption->soi_mode == MP_INET_DFLT) || (serverOption->soi_mode == MP_INET_TCPONLY)){
        if((serverOption->soi_tcpfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            return ESVRSOCK;
        serverAddress.sin_port = htons(serverOption->soi_tcpport);

        if(setsockopt(serverOption->soi_tcpfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)))
            return ESVRSOCKOPT;
        if(bind(serverOption->soi_tcpfd, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in)))
            return ESVRBIND;
        if(listen(serverOption->soi_tcpfd, MP_BACKLOG))
            return ESVRLISTEN;
        if((fdFlag = fcntl(serverOption->soi_tcpfd, F_GETFL, 0)) < 0)
            return ESVRSOCKOPT;
        if(fcntl(serverOption->soi_tcpfd, F_SETFL, fdFlag|O_CLOEXEC) < 0)
            return ESVRSOCKOPT;
    }
    if((serverOption->soi_mode == MP_INET_DFLT) || (serverOption->soi_mode == MP_INET_UDPONLY)){
        if((serverOption->soi_udpfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
            return ESVRSOCK;
        serverAddress.sin_port = htons(serverOption->soi_udpport);

        if(bind(serverOption->soi_udpfd, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in)))
            return ESVRBIND;
    }
    return 0;
}

static int localServerInitialize(const int type, struct svropt_local *__restrict__ serverOption)
{
    int enable = 1;
    struct sockaddr_un serverAddress;

    switch(type){
        case SOCK_DGRAM:
        case SOCK_STREAM:
            break;
        default:
            return ESVRTYPE;
    }

    if((serverOption->sol_svrfd = socket(AF_LOCAL, type, 0)) < 0)
        return ESVRSOCK;
    unlink(serverOption->sol_parh);
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sun_family = AF_LOCAL;
    strcpy(serverAddress.sun_path, serverOption->sol_parh);

    if(type == SOCK_STREAM){
        if(setsockopt(serverOption->sol_svrfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)))
            return ESVRSOCKOPT;        
    }
    if(bind(serverOption->sol_svrfd, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_un)))
        return ESVRBIND;

    if(type == SOCK_STREAM){
        if(listen(serverOption->sol_svrfd, MP_BACKLOG))
            return ESVRLISTEN;
    }
    return 0;
}

extern int mpServerInitialize(int family, const int type, void *__restrict__ serverOption)
{
    int errorCode;

    switch(family){
        case AF_INET:
        case MP_AF_INETMIX:{
            if((errorCode = inetServerInitialize(type, serverOption)) < 0)
                return errorCode;
            break;
        }
        case AF_LOCAL:{
            if((errorCode = localServerInitialize(type, serverOption)) < 0)
                return errorCode;
            break;
        }
        case AF_INET6:
        default:
            return ESVRNFAMILY;
    }    
    return 0;
}

static int mpDefaultServer(const struct svropt_inet const *opt, _DIR clientServiceDIR)
{
    _FD clientFD;
    fd_set readSet;
    pid_t clientPID;
    char ip[INET_ADDRSTRLEN], peerAddr[INET_ADDRSTRLEN+10], tcpClientFDInChar[10], udpBuffer[MP_MAXLINE];
    struct sockaddr_in tcpClientAddress, udpClientAddress;
    socklen_t socketLen;

    FD_ZERO(&readSet);
    for(;;){
        FD_SET(opt->soi_tcpfd, &readSet);
        FD_SET(opt->soi_udpfd, &readSet);
        if(select((opt->soi_tcpfd>opt->soi_udpfd?opt->soi_tcpfd:opt->soi_udpfd)+1, &readSet, NULL, NULL, NULL) < 0){
            if(errno == EINTR)
                continue;
            else
                return ESVRWAIT;
        }
        if(FD_ISSET(opt->soi_tcpfd, &readSet)){
            socketLen = sizeof(tcpClientAddress);
            if((clientFD = accept(opt->soi_tcpfd, (struct sockaddr *)&tcpClientAddress, &socketLen)) < 0){
                if(errno == EINTR)
                    continue;
                else
                    return ESVRWAIT;
            }
            inet_ntop(AF_INET, &tcpClientAddress.sin_addr, ip, sizeof(ip));
            snprintf(tcpClientFDInChar, sizeof(tcpClientFDInChar), "%d", clientFD);
            snprintf(peerAddr, sizeof(peerAddr), "%s:%d", ip, tcpClientAddress.sin_port);

            if((clientPID = fork()) == 0)
                if(execlp(clientServiceDIR, "[inetser]", tcpClientFDInChar, peerAddr, (char *)0))
                    exit(ESVRSER);
            close(clientFD);
            continue;
        }
        if(FD_ISSET(opt->soi_udpfd, &readSet)){
            socketLen = sizeof(udpClientAddress);
            memset(udpBuffer, 0, sizeof(udpBuffer));
            if(recvfrom(opt->soi_udpfd, udpBuffer, sizeof(udpBuffer), 0, (struct sockaddr *)&udpClientAddress, &socketLen) < 0){
                if(errno == EINTR)
                    continue;
                else
                    return ESVRWAIT;
            }
            printf("udp rcv: %s\n", udpBuffer);
        }
    }
}

extern int mpServerStart(const void const *opt, void *__restrict args, int (*serverFunc)(const void const *opt, void *__restrict argv))
{
    int errorCode;

    if((serverFunc == MP_NULLSVR) || (serverFunc == NULL))
        return 0;
    else if(serverFunc == MP_DFLTSVR){
        if((errorCode = mpDefaultServer((struct svropt_inet *)opt, (char *)args)))
            return errorCode;
    }

    errorCode = serverFunc(opt, args);
    return errorCode;
}

extern void (*mpSignal(int actSignal, void (*func)(int)))(int)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if(actSignal == SIGALRM){
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    }else
        act.sa_flags |= SA_RESTART;

    if(sigaction(actSignal, &act, &oact) < 0)
        return(SIG_ERR);
    return(oact.sa_handler);
}

extern int mpDaemonize(void)
{
    int i;
    _FD stdIn, stdOut, stdErr;
    struct rlimit limit;
    struct sigaction signalAtion;

    umask(0);
#ifdef RLIMIT_NOFILE
    if(getrlimit(RLIMIT_NOFILE, &limit) < 0)
        return -1;
#endif
    if(fork() != 0)
        exit(0);
    setsid();

    signalAtion.sa_handler = SIG_IGN;
    sigemptyset(&signalAtion.sa_mask);
    signalAtion.sa_flags = 0;
    if(sigaction(SIGHUP, &signalAtion, NULL) < 0)
        return -1;

    if(chdir("/") < 0)
        return -1;
#ifdef RLIM_INFINITY
    if(limit.rlim_max == RLIM_INFINITY)
        limit.rlim_max = 1024;
#endif
    for(i=0; i<limit.rlim_max; i++)
        close(i);

    stdIn = open("/dev/null", O_RDWR);
    stdOut = dup(0);
    stdErr = dup(0);

    if(stdIn != 0 || stdOut != 1 || stdErr != 2)
        return -1;

    return 0;
}

extern int mpLockPossess(_DIR lockFile)
{
    _FD lockFD;
    int len;
    struct flock writeLock;
    char pidBuf[17], fileNameBuf[100];

    if((len = strlen(lockFile)) > 100)
        return -1;

    if((lockFD = open(lockFile, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0)
        return -1;
    writeLock.l_type = F_WRLCK;
    writeLock.l_start = 0;
    writeLock.l_len = 0;
    writeLock.l_whence = SEEK_SET;
    if(fcntl(lockFD, F_SETLK, &writeLock) < 0){
        if(errno == EACCES || errno == EAGAIN)
            return 1;
        return -1;
    }
    if(ftruncate(lockFD, 0) == -1)
        return -1;
    snprintf(pidBuf, sizeof(pidBuf), "%ld", (long)getpid());
    if(mpWrite(lockFD, pidBuf, sizeof(pidBuf)) < 0)
        return -1;
    return 0;
}
