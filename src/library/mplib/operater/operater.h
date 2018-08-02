#ifndef _OPERATER_H
#define _OPERATER_H

#include "mpfsw.h"
#include "mpobp.h"

typedef struct Operater{
    void (*operate)(void *subgroup);
    void (*execute)(void *subgroup, Task *task);
    void *(*getSubroupStatus)(void *subgroup);
    void *subgroup;
    Task *task
}MPOperater;

#endif
