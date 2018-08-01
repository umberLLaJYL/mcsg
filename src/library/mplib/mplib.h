#ifndef _MPLIB_H
#define _MPLIB_H

#include <sys/wait.h>
#include <sys/un.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <getopt.h>
#include <pthread.h>

#include "mpio.h"

#include "controls/osw.h"
#include "controls/fsw.h"
#include "controls/pd.h"

#include "strategy/obp.h"
#include "strategy/mpfsw.h"
#include "../murmurhash3/murmurhash3.h"

/****************************************/
/*                macro                 */
/****************************************/
#define MP_DEBUG

#ifndef AF_LOCAL
#define	AF_LOCAL AF_UNIX
#endif

#ifndef SIG_ERR
#define	SIG_ERR ((void (*)(int))-1)
#endif
#ifndef SIG_DFL
#define	SIG_DFL ((void (*)(int))0)
#endif
#ifndef SIG_IGN
#define	SIG_ERR ((void (*)(int))1)
#endif

#define new(obj, opt...) obj##Construct(malloc(sizeof(obj)), ##opt)
#define delete(obj, ptr) do{obj##Destruct(ptr); free(ptr);}while(0)

#define MP_SETTINGDIR "./settings.json"
#define MP_TMPDIR "/tmp/mcsg/"

#define SOCK_MIX 10

#define MP_INET_DFLT    0
#define MP_INET_TCPONLY 1
#define MP_INET_UDPONLY 2

#define ESVRSOCK    -1  /* server can not create socket */
#define ESVRBIND    -2  /* server can not bind with address */
#define ESVRLISTEN  -3  /* server can not be activated */
#define ESVRSOCKOPT -4  /* server can not option socket */
#define ESVRNFAMILY -5  /* MCSG can not support the server family */
#define ESVRWAIT    -6  /* server can not be initialized */
#define ENICDISEN   -7  /* NIC is disable */
#define ENONIC      -8  /* MCSG can not support the NIC */
#define ESETTING    -9  /* MCSG fail to operate the settings file */
#define ESVRSER     -10 /* server fail to execute client service */
#define ESELECT     -11 /* MCSG get an error from 'select' */
#define ESVRTYPE    -12 /* MCSG can not identify socket types */

#define MP_BACKLOG 8 
#define MP_MAXSLOT 32
#define MP_MAXCLIENT 16
#define MP_MAXNIC  4

/****************************************/
/*           class definetion           */
/****************************************/
typedef in_addr_t _IP, _GW, _SM;
typedef in_port_t _PORT;

#pragma pack(1)

typedef struct{
    int stat;
    int type;
    char mn[9];
}slot_t;

typedef struct{
    _PORT port;
    _SM nm;
    _IP ip;
    _GW gw;
}inet_t;

typedef struct{
	int addr;      /* command address */
	int pstat;     /* power status */
	int smax;      /* device slots */
	char mn[16];    /* device machine number */
	inet_t nic[MP_MAXNIC];
	// slot_t *slist;
}mp_dev_t;

#pragma pack()

typedef struct{
    int target;
    int status;
    char action[8];
    char reply[128];
}TaskNode;

typedef struct iTask{
    struct iTask *next;
    pthread_mutex_t lock;
    long id;
    long timestamp;
    int issue;
    int status;
    TaskNode command[24];
}Task;

typedef struct iContril{
    struct iContril *next;
    void (*execute)(char *command);
    void (*operate)(struct iContril *control);
    void *attribute;
    int type;
    int label;
    char identity[8];
}Control;

typedef struct oDevice{
    void (*operater)(struct oDevice *device, Task *iTask);
    void *(*getSubroupStatus)(Control *subgroup);
    Control *subgroup;
    int address;
    char rule[4096];
    char model[24];
    char sn[16];
}MPDevice;

/****************************************/
/*         function declaration         */
/****************************************/
extern void (*mpSignal(int actSignal, void (*handler)(int)))(int);
extern int mpDaemonize(void);
extern int mpLockPossess(_DIR lockFile);

#endif
