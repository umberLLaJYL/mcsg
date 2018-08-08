#ifndef _CONTROL_H
#define _CONTROL_H

#include "osw.h"
#include "fsw.h"
#include "pd.h"

typedef struct Contril{

    struct Contril *next;

    void (*execute)(char *command);
    void (*operate)(struct iContril *control);

    void *attribute;
    void *data;
    
    int type; 
    int label;
    char identity[8];
}Control;

#endif
