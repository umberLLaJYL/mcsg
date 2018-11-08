#ifndef _MPIO_H
#define _MPIO_H

/**
 * unix(POSIX)/C library
 */
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

/**
 * C++ library
 */
#include <iostream>
#include <fstream>

/****************************************/
/*                macro                 */
/****************************************/
#define MP_MAXLINE 4096

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
