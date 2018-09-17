#ifndef _MPLIB_H
#define _MPLIB_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <sys/resource.h>
#include <signal.h>
#include <getopt.h>

#include <pthread.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <thread>
#include <map>

#include "mpsocket/mpsocket.h"

// #include "../murmurhash3/murmurhash3.h"

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

#define _DIR const char * const

typedef int _FD;
typedef in_addr_t _IP, _GW, _SM;
typedef in_port_t _PORT;

/****************************************/
/*         function declaration         */
/****************************************/
extern void (*mpSignal(int actSignal, void (*handler)(int)))(int);
extern int mpDaemonize(void);
extern int mpLockPossess(_DIR lockFile);

class GPIO {
private:
    static const _FD _export;
    static const _FD _unexport;

    _FD _gpioDirection;
    _FD _gpioValue;
    _FD _gpioEdge;

    int index;
    
    static bool _register(const _FD, const int);

    static bool _exportGPIO(const int);
    static bool _unexportGPIO(const int);

    bool _setGPIO(_FD, const std::string &);

    bool _getOption(const std::string &, std::string &);

public:
    GPIO(const int);
    GPIO(const int, const std::string &);
    GPIO(const int, const std::string &, const int);
    ~GPIO();

    GPIO &operator = (const int);
    bool operator == (const int);
    bool operator != (const int);

    bool output();
    bool input();

    bool pullUp();
    bool pullDown();

    int getIndex() const;
    int getValue();
    int getDirection();

    bool irqNone();
    bool irqRising();
    bool irqFalling();
    bool irqBoth();
};

#include "gpio.cpp"

#endif
