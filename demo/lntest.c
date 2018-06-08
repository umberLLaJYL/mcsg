#include <sys/types.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <errno.h>
#include <stdint.h>
#include <fcntl.h>

#include "../src/json/cJSON.h"
#include "../src/mpmsg.h"

extern struct msgln *mpGenerateWorkQueue(void)
{
    struct msgln *head;

    if((head = (struct msgln *)malloc(sizeof(struct msgln))) == NULL)
        return NULL;
    head->ml_next = NULL;

    return head;
}

extern struct msgln *mpMessageReg(struct msgln *list, const char *msg)
{
    unsigned int lnid = 0;
    struct msgln *node, *tail;
    
    node = list;
    while(node->ml_next){
        lnid++;
        node = node->ml_next;
    }
    if((tail = (struct msgln *)malloc(sizeof(struct msgln))) == NULL)
        return NULL;

    tail->ml_lnid = lnid;
    
    tail->ml_next = NULL;
    node->ml_next = tail;

    memcpy(tail->ml_data, msg, MP_MAXLINE);
}


extern struct msgln *mpMessagePase(const char *msg, struct msgln *list)
{
    char *cp;
    int lBrace = 0, rBrace = 0;
    int maxLen, ret;
    struct msgln *node;

    node = list->ml_next;

    cp = node->ml_data;
    maxLen = strlen(node->ml_data);
    while(--maxLen){
        if(*cp == '{')
            lBrace++;
        else if(*cp == '}')
            rBrace++;
        cp++;
    }
    node->ml_lbrace += lBrace;
    node->ml_rbrace += rBrace;
    
    if((node->ml_lbrace != node->ml_rbrace) && (node->ml_lbrace)){
        node->ml_flag = 0;
    }    
}

int main(int ac, char *av[])
{
    struct msgln *mlist;

    printf("%lu\n", sizeof(int));
}
