#ifndef _MPLIB_H
#define _MPLIB_H

/**
 * unix(POSIX)/C library
 */
#include <sys/wait.h>
#include <time.h>
#include <sys/resource.h>
#include <signal.h>
#include <getopt.h>
#include <pthread.h>

/**
 * C++ library
 */
#include <string>
#include <vector>
#include <cstddef>
#include <thread>
#include <map>

/**
 * custom library
 */
#include "mpio.h"
#include "mpsocket.h"

#include "Device/Device.h"

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

typedef in_addr_t _IP, _GW, _SM;
typedef in_port_t _PORT;

class GPIO;

/****************************************/
/*         function declaration         */
/****************************************/
extern void (*mpSignal(int actSignal, void (*handler)(int)))(int);
extern int mpDaemonize(void);
extern int mpLockPossess(_DIR lockFile);

#endif
