#ifndef _MPLOG_H
#define _MPLOG_H

#include <syslog.h>
#include "../../src/mplib/mpmod.h"

#define MPLOGD_CONFDIR "/etc/mplogd.conf"
#define MPLOGD_SOCK "/var/run/mplogd.socket"

#ifndef LOG_EMERG
#define LOG_EMERG 0
#endif
#ifndef LOG_ALERT
#define LOG_ALERT 1
#endif
#ifndef LOG_CRIT
#define LOG_CRIT 2
#endif
#ifndef LOG_ERR
#define LOG_ERR 3
#endif
#ifndef LOG_WARNING
#define LOG_WARNING 4
#endif
#ifndef LOG_NOTICE
#define LOG_NOTICE 5
#endif
#ifndef LOG_INFO
#define LOG_INFO 6
#endif
#ifndef LOG_DEBUG
#define LOG_DEBUG 7
#endif

#define MPLOGD_MAXLOGBUF 2048

#define MPLOG_DEFAULT 0
#define MPLOG_NETONLY   1
#define MPLOG_LOCALVNET 2

typedef struct{
    int facility;
    int priority;
    char Ident[128];
    char logBuffer[MPLOGD_MAXLOGBUF];
}mplog_t;

extern void mpOpenLog(const char *ident, int logopt, int facility);
extern void mpCloseLog(void);
extern void mpLog(int priority, const char *message, ...);

#endif