#ifndef _MPSVROP_H
#define _MPSVROP_H

// #include <pthread.h>
#include "../../library/mplib/mpmod.h"
#include "../../library/json/cJSON.h"

typedef struct{
    CONTROL *next;
    int (*execute)(void *args);
    char *rule;
    int type;
}CONTROL;

typedef struct{
    int (*server)(void);
    int (*parser)(char *__restrict in, void *__restrict out);
    int (*executor)(void *task);
    CONTROL subgroup;
    char model[100];
    char version[15];
    char lsocket[104];
}MPSVR;

// struct taskln{
//     struct svrtask *t_next;
//     int t_src;
//     int t_dest;
//     int t_type;
//     long t_id;
//     pthread_mutex_t t_lock;
//     char t_buf[9];
// };

extern int mpsvrConfigure(MPSVR *__restrict mpsvr);

#endif
