#ifndef _MPMSG_H
#define _MPMSG_H

#include <sys/stat.h>
#include "./mplib/mpmod.h"
#include "./murmurhash3/murmurhash3.h"
#include "./json/cJSON.h"

#define MP_MSGSEED 170
#define MP_MSGENCODE 0x80000000

#define MSG_SYNC (unsigned int)0x92162ca4
#define MSG_ACK  (unsigned int)0x5df37840
#define MSG_CMD  (unsigned int)0x148d1cbc

typedef struct{
	int lm_len;   /* communicate target */
	int lm;     /* message cade: 0, set; 1, check */
	char lm_data[MP_MAXLINE];  /* message buffer*/
}msg_t;

struct msgln{
	struct msgln *ml_next;
	unsigned int ml_lnid;
	unsigned int ml_msgid;
	unsigned int ml_rbrace;
	unsigned int ml_lbrace;
	unsigned int ml_wtime;
	int ml_flag;
	char ml_buf[MP_MAXLINE];
};

extern int mpGenerateMessage(char *__restrict messageBuffer, const char *const type, ...);

#endif
