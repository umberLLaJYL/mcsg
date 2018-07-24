#ifndef _FSW_H
#define _FSW_H

typedef struct fsw{
    unsigned int channelnum;
    unsigned int channel;
}fswAttribute;

extern void fswExecute(char *command);

#endif
