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
#include <pthread.h>
 
struct test_t{
    int a, b;
    char buf[4096];
};

void *func(void *args)
{
    struct test_t *arg;

    arg = (struct test_t *)args;
    printf("%d, %d, %s", arg->a, arg->b, arg->buf);
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    struct test_t test;

    test.a = 10;
    test.b = 1238381;
    strcpy(test.buf, "asdlndljanlcasnc\n");
    if(pthread_create(&tid, NULL, func, &test))
        perror("pthread");
    
    sleep(2);
    return 0;
}

