#ifndef _FSW_H
#define _FSW_H

typedef struct ifswAttribute{
    unsigned int channelnum;
    unsigned int channel;
}fswAttribute;

extern void fswExecute(char *command);

#endif
