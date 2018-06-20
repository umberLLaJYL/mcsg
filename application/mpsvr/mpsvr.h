#ifndef _MPSVR_H
#define _MPSVR_H

#include <pthread.h>
#include "../../src/mplib/mpmod.h"
#include "../../src/json/cJSON.h"

#define MP_LOCALSVRDIR "/tmp/mcsg/local.socket"

struct taskln{
    struct svrtask *t_next;
    int t_src;
    int t_dest;
    int t_type;
    long t_id;
    pthread_mutex_t t_lock;
    char t_buf[MP_MAXLINE];
};

#endif
