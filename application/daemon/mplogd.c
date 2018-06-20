#include "mplog.h"

struct logopt{
    int lo_mode;
    _PORT lo_port;
    off_t lo_size;
    struct in_addr lo_addr;
    char lo_path[104];
};

static void configInitialize(_DIR configFile, struct logopt *__restrict mplogdOption)
{
    char *cp, ip[INET_ADDRSTRLEN], configuration[MP_MAXLINE];
    FILE *confFP;

    if((confFP = fopen(configFile, "r")) == NULL)
        mpExit("mplogd: can not open '%s'", MPLOGD_CONFDIR);
    while(fgets(configuration, MP_MAXLINE, confFP) != NULL){
        if(strncmp(configuration, "$Mode", 5) == 0){
            if(strstr(configuration, "NETONLY") != NULL)
                mplogdOption->lo_mode = MPLOG_NETONLY;
            else if(strstr(configuration, "LOCALVNET") != NULL)
                mplogdOption->lo_mode = MPLOG_LOCALVNET;
            else if(strstr(configuration, "DEFAULT") != NULL)
                mplogdOption->lo_mode = MPLOG_DEFAULT;
            else
                mpQuit(1, "mplogd initialize fail: error log mode\n");
        }else if(strncmp(configuration, "$UploadAddress", 14) == 0){
            cp = configuration;
            if(strchr(configuration, ':') == NULL){

            }            
            while((*cp > '9') || (*cp < '0'))
                cp++;
            strncpy(ip, cp, strlen(cp) - strlen(strchr(configuration, ':')));
            if(inet_pton(AF_INET, ip, &mplogdOption->lo_addr) != 1)
                mpExit("mplogd: initialize fail");
            mplogdOption->lo_port = atoi(++cp);
        }else if(strncmp(configuration, "$LogDirectory", 13) == 0){
            if((cp = strchr(configuration, '/')) == NULL)
                mpQuit(1, "mplogd: initialize fail: error log directory\n");
            if(strlen(cp) > 104)
                mpQuit(1, "mplogd: initialize fail: log directory too long\n");
            strncpy(mplogdOption->lo_path, cp, strlen(cp)-1);
        }else if(strncmp(configuration, "$MaximumFileSize", 15) == 0){
            cp = configuration;
            while((*cp > '9') || (*cp < '0'))
                cp++;
            if((mplogdOption->lo_size = atoi(cp)) < 1024)
                mpQuit(1, "mplogd: initialize fail: error file size(1023<size<65535)\n");
        }
    }
    fclose(confFP);
}

static void optionInitialize(int argc, char *argv[], struct logopt *__restrict__ mplogdOption)
{
    int opt;
    char *cp, ip[INET_ADDRSTRLEN];

    while((opt = getopt(argc, argv, "cr:p:s:")) != -1){
        switch(opt){
            case 'c':
                return;
            case 'r':{
                if((cp = strrchr(optarg, ':')) == NULL){

                }
                strncpy(ip, optarg, strlen(optarg) - strlen(strchr(optarg, ':')));
                if(inet_pton(AF_INET, ip, &mplogdOption->lo_addr) != 1){

                }
                mplogdOption->lo_port = atoi(++cp);
                break;
            }
            case 'p':{
                strncpy(mplogdOption->lo_path, optarg, 104);
                break;
            }
            case 's':{
                if((mplogdOption->lo_size = atoi(optarg)) < 1024){

                }
                break;
            }
            case '?':
            default: printf("Usage: \n");exit(0);
        }
    }
}

int main(int argc, char *argv[])
{
    _FD logFD;
    struct sockaddr_un serverAddress;
    struct svropt_local serverOption;
    struct logopt logOption;
    struct stat fileStat;
    int errorCode;
    socklen_t sockLen;
    mplog_t logBuf;

    if(argc < 2)
        mpQuit(1, "usage\n");

    configInitialize(MPLOGD_CONFDIR, &logOption);
    optionInitialize(argc, argv, &logOption);

    if(mpDaemonize())
        mpQuit(1, "mplogd can not be daemonize\n");

    if((errorCode = mpLockPossess("/var/run/mplogd.pid")) != 0)
        exit(errorCode);
    
    if(access(logOption.lo_path, F_OK) == -1)
        if((logFD = open(logOption.lo_path, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0)
            return -1;
    if((logFD = open(logOption.lo_path, O_RDWR|O_APPEND)) < 0)
        return -1;

    strncpy(serverOption.sol_parh, MPLOGD_SOCK, sizeof(serverOption.sol_parh)); 
    if((errorCode = mpServerInitialize(AF_LOCAL, SOCK_DGRAM, &serverOption)) < 0)
        return errorCode;
    for(;;){
        sockLen = sizeof(serverAddress);
        if(recvfrom(serverOption.sol_svrfd, &logBuf, sizeof(logBuf), 0, (struct sockaddr *)&serverAddress, &sockLen) < 0)
            return -1;

        printf("%s", logBuf.logBuffer);

        if(fstat(logFD, &fileStat))
            continue;
        if(fileStat.st_size > logOption.lo_size){
            char bkpDir[128];
            
            snprintf(bkpDir, sizeof(bkpDir), "%s.bkp", logOption.lo_path);
            unlink(bkpDir);
            if(rename(logOption.lo_path, bkpDir))
                continue;
            logFD = open(logOption.lo_path, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        }
        mpWrite(logFD, logBuf.logBuffer, strlen(logBuf.logBuffer));
        // if(logBuf.extent != -1){
        //     if(logBuf.priority < logBuf.extent){

        //     }
        // }
    }
    return -1;
}
