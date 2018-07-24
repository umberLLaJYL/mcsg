#ifndef _MPIO_H
#define _MPIO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>
#include <fcntl.h>

/****************************************/
/*                macro                 */
/****************************************/
#define MP_MAXLINE 4096
#define _DIR const char * const

/****************************************/
/*           class definetion           */
/****************************************/
typedef int _FD;

/****************************************/
/*         function declaration         */
/****************************************/
extern void mpQuit(int exitCode, const char *__restrict fmtMessage, ...);
extern void mpExit(const char *__restrict fmtMessage, ...);
extern int mpSystem(const char *__restrict fmtCommand, ...);

extern ssize_t mpRead(_FD whatToRead, void *__restrict readToWhere, size_t numToRead);
extern ssize_t mpRecv(_FD whatToRead, void *__restrict readToWhere, size_t numToRead, int flag);
extern ssize_t mpWrite(_FD whatToWrite, const void *__restrict dataToWrite, size_t numToWrite);

#endif