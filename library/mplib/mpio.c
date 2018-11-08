#include "mpio.h"

/**********************************************************************/
/* function: format a message, pirnt this message to stdout and exit  */
/*           the program with excode.                                 */
/* input: excode: an exit code to pass to the function 'exit';        */
/*        fmt: a formative string which you want to print;            */
/* output: void.                                                      */
/**********************************************************************/
extern void mpQuit(int exitCode, const char *__restrict fmtMessage, ...)
{
    va_list ap;

    va_start(ap, fmtMessage);
    vprintf(fmtMessage, ap);
    va_end(ap);
    exit(exitCode);
}

/**********************************************************************/
/* function: format a message with system error message, pirnt this   */
/*           message to stdout and exit the program with excode.      */
/*        fmt: a formative string which you want to print;            */
/* output: void.                                                      */
/**********************************************************************/
extern void mpExit(const char *__restrict fmtMessage, ...)
{
    va_list ap;
    char buf[MP_MAXLINE];

    va_start(ap, fmtMessage);
    vsnprintf(buf, MP_MAXLINE-1, fmtMessage, ap);
    snprintf(buf+strlen(buf), MP_MAXLINE-strlen(buf)-1, ": %s\n", strerror(errno));
    fputs(buf, stdout);
    va_end(ap);
    exit(errno);
}

/**********************************************************************/
/* function: format a command line, and leave it to the shell.        */
/* input: fmt: a formative string which you want to print;            */
/* output: result of the function 'system'.                           */
/**********************************************************************/
extern int mpSystem(const char *__restrict fmtCommand, ...)
{
    va_list ap;
    char buf[MP_MAXLINE];

    va_start(ap, fmtCommand);
    vsprintf(buf, fmtCommand, ap);
    va_end(ap);

    return (system(buf));
}

extern ssize_t mpRead(_FD whatToRead, void *__restrict readToWhere, size_t numToRead)
{
    ssize_t numRead;
    size_t totalRead = 0;

    while(totalRead < numToRead){
        if((numRead = read(whatToRead, readToWhere+totalRead, numToRead-totalRead)) < 0){
            if(errno == EINTR)
                continue;
            else if(errno == EAGAIN)
                break;
            else
                return -1;
        }else if(numRead == 0)
            break;
        totalRead += numRead;
    }
    return totalRead;
}

extern ssize_t mpRecv(_FD whatToRead, void *__restrict readToWhere, size_t numToRead, int flag)
{
    ssize_t numRead;
    size_t totalRead = 0;
    int fdFlag;

    if((fdFlag = fcntl(whatToRead, F_GETFL, 0)) < 0)
        return -1;
    if(flag == 1){
        if(fcntl(whatToRead, F_SETFL, fdFlag|O_NONBLOCK) < 0)
            return -1;
    }else if(flag == 0){
        if(fcntl(whatToRead, F_SETFL, fdFlag&(~O_NONBLOCK)) < 0)
            return -1;
    }

    while(totalRead < numToRead){
        if((numRead = read(whatToRead, readToWhere+totalRead, numToRead-totalRead)) < 0){
            if(errno == EINTR)
                numRead = 0;
            else if(errno == EAGAIN)
                break;
            else{
                fcntl(whatToRead, F_SETFL, fdFlag);
                return -1;
            }
        }else if(numRead == 0)
            break;
        totalRead += numRead;
    }
    fcntl(whatToRead, F_SETFL, fdFlag);
    return totalRead;
}

extern ssize_t mpWrite(_FD whatToWrite, const void *__restrict dataToWrite, size_t numToWrite)
{
    ssize_t numWrite;
    size_t totalWrite = 0;

    while(totalWrite < numToWrite){
        if((numWrite = write(whatToWrite, dataToWrite+totalWrite, numToWrite-totalWrite)) < 0){
            if(errno == EINTR)
                continue;
            else if(errno == EAGAIN)
                break;
            else
                return -1;
        }
        totalWrite += numWrite;
    }
    return totalWrite;
}
