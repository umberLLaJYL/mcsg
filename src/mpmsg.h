#ifndef _MPMSG_H
#define _MPMSG_H

#include <sys/stat.h>
#include "./murmurhash3/murmurhash3.h"

#define MP_MAXID 64
#define MP_MSGSEED 170
#define MP_MSGENCODE 0x80000000

#define MSG_SYNC (unsigned int)0x92162ca4
#define MSG_ACK  (unsigned int)0x5df37840
#define MSG_CMD  (unsigned int)0x148d1cbc

typedef struct{
	int lm_len;   /* communicate target */
	int lm;     /* message cade: 0, set; 1, check */
	char *lm_data;  /* message buffer*/
}msg_t;

extern int mpGenerateMessage(char *__restrict messageBuffer, const char *const type, ...);
extern int mpParseMessage(const char *const message, char *msgID);

#endif
