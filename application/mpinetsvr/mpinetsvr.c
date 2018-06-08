#include "../../src/mplib/mpmod.h"
#include "../daemon/mplog.h"

void clearUp(int singo)
{
    wait(NULL);
}

static void optionInitialize(int argc, char *argv[], struct svropt_inet *__restrict__ svrverOption)
{
    int opt;
    _PORT port0, port1;
    static struct option options[] = {
        {"default", optional_argument, NULL, 'd'},
        {"tcponly", optional_argument, NULL, 't'},
        {"udponly", optional_argument, NULL, 'u'}
    };
    
    while((opt = getopt_long(argc, argv, "v", options, NULL)) != -1){
        switch(opt){
            case 'v':{
                
                break;
            }
            case 'd':{
                svrverOption->so_mode = MP_INET_DFLT;
                svrverOption->so_tcpport = atoi(optarg);
                svrverOption->so_udpport = atoi(argv[optind]);
                if((svrverOption->so_tcpport < 1024) || (svrverOption->so_udpport < 1024))
                    mpQuit(1, "mpinetsvr: invalid port\n");
                break;
            }
            case 't':{
                svrverOption->so_mode = MP_INET_TCPONLY;
                svrverOption->so_tcpport = atoi(optarg);
                if(svrverOption->so_tcpport < 1024)
                    mpQuit(1, "mpinetsvr: invalid port\n");
                break;
            }
            case 'u':{
                svrverOption->so_mode = MP_INET_UDPONLY;
                svrverOption->so_tcpport = atoi(optarg);
                if(svrverOption->so_udpport < 1024)
                    mpQuit(1, "mpinetsvr: invalid port\n");
                break;
            }
            case '?':
            default: printf("Usage: \n");exit(0);
        }
    }
}

/* main function of the TCP/IPv4 server */
int main(int argc, char *argv[])
{
    int mode, errorCode;
    struct svropt_inet serverOprion;

    if(mpLockPossess("/var/run/mpinetsvr.pid"))
        mpQuit(1, "mpinetsvr is running already\n");

    optionInitialize(argc, argv, &serverOprion);
    mpOpenLog("MCSG", 0, 7);

    if((errorCode = mpServerInitialize(MP_AF_INETMIX, SOCK_STREAM, &serverOprion)) < 0)
        mpExit("mpinetsvr initialize fail: %d", errorCode);
    /* register a 'SIGCHILD' handler for server */
    if(mpSignal(SIGCHLD, clearUp) == SIG_ERR)
        mpExit("mpinetsvr register handler fail");

    printf("mpinetsvr initialized.\n");
    mpLog(LOG_INFO, "mpinetsvr start");

    /* start a 'multiple process blocking i/o' default MP tcp server */
    if((errorCode = mpServerStart(&serverOprion, "./bin/.inetcliser", MP_DFLTSVR)) < 0)
        mpQuit(1, "mpinetsvr shutdown unexpected: %d\n", errorCode);
}
