#include "mpsvrop.h"

// static struct taskln *mpGenerateTaskQueue(void)
// {
//     struct taskln *head;

//     if((head = (struct taskln *)malloc(sizeof(struct taskln))) == NULL)
//         return NULL;
//     head->t_next = NULL;

//     return head;
// }

// static struct msgln *mpAssignTask(struct taskln *list, const char *msg)
// {
//     unsigned int lnid = 0;
//     struct taskln *node, *tail;
    
//     node = list;
//     while(node->t_next){
//         lnid++;
//         node = node->t_next;
//     }
//     if((tail = (struct taskln *)malloc(sizeof(struct taskln))) == NULL)
//         return NULL;

//     tail->ml_lnid = lnid;
    
//     tail->ml_next = NULL;
//     node->ml_next = tail;

//     memcpy(tail->ml_buf, msg, MP_MAXLINE);
// }

// void *cothread(void *args)
// {
//     struct taskln *task;

//     sleep(1);

//     task = (struct taskln*)args;

//     pthread_exit(NULL);
// }

int main(int argc, char *argv[])
{
    MPSVR mpsvr;
    // pthread_t cothreadID;

    if(mpsvrConfigure(&mpsvr))
        mpExit("mpsvr: configure fail");

    if(mpLockPossess("/var/run/mpsvr.pid"))
        mpQuit(1, "mpsvr: already running\n");

    mpsvr.server();

    // if((errorCode = pthread_create(&cothreadID, NULL, cothread, NULL)) != 0)
    //     mpExit("mpser initialize co-thread fail: %d", errorCode);

    // if((errorCode = mpServerStart(&serverOprion.sol_svrfd, &ttyFD, pollingServer)) < 0)
    //     mpQuit(errorCode, "mpsvr shutdown unexpected: %d\n", errorCode);
}
