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
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>

// #include "../src/json/cJSON.h"
// #include "../src/mpmsg.h"

// extern struct msgln *mpGenerateWorkQueue(void)
// {
//     struct msgln *head;

//     if((head = (struct msgln *)malloc(sizeof(struct msgln))) == NULL)
//         return NULL;
//     head->ml_next = NULL;

//     return head;
// }

// extern struct msgln *mpMessageReg(struct msgln *list, const char *msg)
// {
//     unsigned int lnid = 0;
//     struct msgln *node, *tail;
    
//     node = list;
//     while(node->ml_next){
//         lnid++;
//         node = node->ml_next;
//     }
//     if((tail = (struct msgln *)malloc(sizeof(struct msgln))) == NULL)
//         return NULL;

//     tail->ml_lnid = lnid;
    
//     tail->ml_next = NULL;
//     node->ml_next = tail;

//     memcpy(tail->ml_buf, msg, MP_MAXLINE);
// }


// extern struct msgln *mpMessagePase(const char *msg, struct msgln *list)
// {
//     char *cp;
//     int lBrace = 0, rBrace = 0;
//     int maxLen, ret;
//     struct msgln *node;

//     node = list->ml_next;

//     cp = node->ml_buf;
//     maxLen = strlen(node->ml_buf);
//     while(--maxLen){
//         if(*cp == '{')
//             lBrace++;
//         else if(*cp == '}')
//             rBrace++;
//         cp++;
//     }
//     node->ml_lbrace += lBrace;
//     node->ml_rbrace += rBrace;
    
//     if((node->ml_lbrace != node->ml_rbrace) && (node->ml_lbrace)){
//         node->ml_flag = 0;
//     }    
// }

int main(int ac, char *av[])
{
    int speed, i;
    struct timeval timev;
    fd_set readSet;

    FD_ZERO(&readSet);
    FD_SET(0, &readSet);
    
    timev.tv_sec = 5;
    timev.tv_usec = 0;

    printf("%ld\n", timev.tv_sec);
    select(1, &readSet, NULL, NULL, &timev);
    printf("s: %ld\nus: %ld\n", timev.tv_sec, timev.tv_usec);
}
