#ifndef _MPMOD_H
#define _MPMOD_H

#include <sys/wait.h>
#include <sys/un.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <getopt.h>

#include "mpio.h"
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

struct svropt_inet{
	int (*soi_procfunc)(const char *__restrict, ...);
	int soi_mode;
	int soi_tcpport, soi_udpport;
	_FD soi_tcpfd, soi_udpfd;
};

#pragma pack(1)

/* OSW structrue */
typedef struct{
	int lock;  /* link lock */
	int line;  /* link line */
}link_t;
typedef struct{
	int oreq;    /* switch(optical) requirement */
	float opwr;  /* optical power */
	float tpwr;  /* optical power threshold */
}och_t;
typedef struct{
	int type;     /* OSW type */
	int stat;     /* OSW status */
	int hreq;     /* switch(heartbeat) requirement */
	int rreq;     /* switch(Sec2Pri) requirement */
	int sc;       /* switch count */
	int scop;     /* switch count overload protection */
	link_t link;
	char och[0];  /* dynamic data buffer */
}osw_t;

/* FSW structrue */
typedef struct{
	int chx;    /* FSW channel sum */
	int cch;    /* current channel */
	int bch;    /* beginning of scan channel */
	int ech;    /* end of scan channel */
	int stime;  /* scan time */
}fsw_t;

/* OPM structrue */
typedef struct{
	int chx;       /* OPM channel sum */
	char opwr[0];  /* optical power */
}opm_t;

/* OS, WDM structrue */
typedef union{
	int os;   /* OS status */
	int wdm;  /* WDM status */
}ow_t;

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
	char mn[9];    /* device machine number */
	inet_t nic[MP_MAXNIC];
	// slot_t *slist;
}mp_dev_t;

/* LOG structrue */
typedef union{
	unsigned int mask;
	/* log contents */
	struct{
		unsigned char severity;  /* action severity */
		unsigned char type;      /* action type */
		unsigned char obj;       /* action object */
		unsigned char actn;      /* action */
	};
}log_t;

#pragma pack()

/****************************************/
/*         function declaration         */
/****************************************/
// extern _FD mpServerInitialize(int family, const int type, void *__restrict serverOption);
// extern int mpServerStart(const void const *opt, void *__restrict args, int (*serverFunc)(const void const *opt, void *__restrict argv));
extern void (*mpSignal(int actSignal, void (*func)(int)))(int);
extern int mpDaemonize(void);
extern int mpLockPossess(_DIR lockFile);

#endif
