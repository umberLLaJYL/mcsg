#ifndef _OPERATER_H
#define _OPERATER_H

#include "mpfsw.h"
#include "mpobp.h"

typedef struct Op{

    void (*operate)(void *subgroup);
    void (*execute)(void *subgroup, Task *task);
    void *(*getSubroupStatus)(void *subgroup, ...);
    
    Task *task;
    char rule[4096];

}Operater;

#endif
