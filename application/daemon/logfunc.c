#include "mplog.h"

_FD CliFD = -1;
static mplog_t logBuf;

static void mpOpenLogFunc(const char *ident, int logopt, int facility);
static void mpCloseLogFunc(void);
static void mpLogFunc(int priority, const char *message, va_list parmList);

struct logfunc{
    void (*openFunc)(const char *ident, int logopt, int facility);
    void (*closeFunc)(void);
    void (*logFunc)(int priority, const char *message, ...);
    void (*vlogFunc)(int priority, const char *message, va_list args);
};
struct logfunc logFunc = {NULL, NULL, NULL, NULL};

static void mpOpenLogFunc(const char *ident, int logopt, int facility)
{
    char tmpSockDir[104];
    struct sockaddr_un clientAddress, serverAddress;

    if((CliFD = socket(AF_LOCAL, SOCK_DGRAM, 0)) == -1)
        return;

    memset(&clientAddress, 0, sizeof(clientAddress));
    clientAddress.sun_family = AF_LOCAL;
    snprintf(tmpSockDir, sizeof(tmpSockDir), "%s%d.socket", MP_TMPDIR, getpid());
    unlink(tmpSockDir);
    strcpy(clientAddress.sun_path, tmpSockDir);

    if(bind(CliFD, (struct sockaddr *)&clientAddress, sizeof(clientAddress)))
        return;
    unlink(tmpSockDir);

    serverAddress.sun_family = AF_LOCAL;
    strcpy(serverAddress.sun_path, MPLOGD_SOCK);
    if(connect(CliFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)))
        return;

    strncpy(logBuf.Ident, ident, sizeof(logBuf.Ident));
    logBuf.facility = (facility<<3);
}

extern void mpOpenLog(const char *ident, int logopt, int facility)
{
    FILE *confFP;
    char tmpSockDir[104], configuration[MP_MAXLINE];
    struct sockaddr_un clientAddress;

    if((confFP = fopen(MPLOGD_CONFDIR, "r")) == NULL)
        mpExit("mplogd: can not open '%s'", MPLOGD_CONFDIR);
    while(fgets(configuration, MP_MAXLINE, confFP) != NULL){
        if(strncmp(configuration, "$Standard", 9) == 0){
            if((strstr(configuration, "syslogd")) != NULL){
                logFunc.openFunc = openlog;
                logFunc.logFunc = syslog;
                logFunc.vlogFunc = vsyslog;
                logFunc.closeFunc = closelog;
            }
            else if((strstr(configuration, "mplogd")) != NULL){
                logFunc.openFunc = mpOpenLogFunc;
                logFunc.vlogFunc = mpLogFunc;
                logFunc.closeFunc = mpCloseLogFunc;
            }
            else
                printf("mplogd error: error standard\n");
        }
    }
    if(logFunc.openFunc == NULL)
        return;
    logFunc.openFunc(ident, logopt, facility);
}

static void mpCloseLogFunc(void)
{
    close(CliFD);
}

extern void mpCloseLog(void)
{
    if(logFunc.closeFunc == NULL)
        return;
    logFunc.closeFunc();
}

static void mpLogFunc(int priority, const char *message, va_list parmList)
{
    struct sockaddr_un serverAddress;
    char fmtMsg[MPLOGD_MAXLOGBUF-173], *timeInChar;
    time_t curTime;

    curTime = time(NULL);
    timeInChar = ctime(&curTime);
    timeInChar[24] = 0;
    logBuf.priority = priority;

    if(vsnprintf(fmtMsg, sizeof(fmtMsg), message, parmList) < 0)
        return;
    if(snprintf(logBuf.logBuffer, MPLOGD_MAXLOGBUF, "<%d>%s %s[%d]: %s\n", (logBuf.facility|priority), timeInChar, logBuf.Ident, getpid(), fmtMsg) < 0)
        return;

    if(mpWrite(CliFD, &logBuf, sizeof(logBuf)) < 0)
        perror("mplogd error");
}

extern void mpLog(int priority, const char *message, ...)
{
    va_list parmList;

    if(logFunc.vlogFunc == NULL)
        return;
    va_start(parmList, message);
    logFunc.vlogFunc(priority, message, parmList);
    va_end(parmList);
}
