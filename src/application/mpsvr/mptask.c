#include "mptask.h"

static struct taskln *mpGenerateTaskQueue(void)
{
    struct taskln *head;

    if((head = (struct taskln *)malloc(sizeof(struct taskln))) == NULL)
        return NULL;
    head->t_next = NULL;

    return head;
}

static struct msgln *mpAssignTask(struct taskln *list, const char *msg)
{
    unsigned int lnid = 0;
    struct taskln *node, *tail;
    
    node = list;
    while(node->t_next){
        lnid++;
        node = node->t_next;
    }
    if((tail = (struct taskln *)malloc(sizeof(struct taskln))) == NULL)
        return NULL;

    tail->ml_lnid = lnid;
    
    tail->ml_next = NULL;
    node->ml_next = tail;

    memcpy(tail->ml_buf, msg, MP_MAXLINE);
}
