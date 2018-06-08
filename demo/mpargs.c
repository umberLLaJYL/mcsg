#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>
#include <pthread.h>
#include <getopt.h>

struct logopt{
    int lo_mode;
    int lo_port;
    off_t lo_size;
    char lo_addr[16];
    char lo_path[104];
};

int (*fptr)(int *, ...);

int test(int *a, ...)
{
    int b;
    char *c;

    va_list ap;

    va_start(ap, a);
    b = va_arg(ap, int);
    c = va_arg(ap, char *);
    printf("a %d\n", *a);
    printf("b %d\n", b);
    printf("c %s\n", c);
    va_end(ap);
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int i = 9, opt;
    char *port;
    struct logopt logoption;
    static struct option options[] = {
        {"default", 2, NULL, 'a'},
        {"tcponly", 2, NULL, 'b'}
    };
    // printf("argc: %d\n", argc);

    // for(i = 0; i < argc; i++){
    //     printf("argv%i: %s\n", i, argv[i]);
    // }

    
    if((pid = fork()) == 0){
        if(execlp("./argstest", (char *)fptr, (char *)0))
            perror("execlp");
    }
    printf("p: 0x%x\n", &fptr);

    while((opt = getopt_long(argc, argv, "cd:e::", options, NULL)) != -1){
        switch(opt){
            case 'a':{
                break;
            }
            case 'b':{
                printf("b arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
                break;
            }
            case 'c':{
                printf("c arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
                break;
            }
            case 'd':{
                strncpy(logoption.lo_addr, optarg, strlen(optarg) - strlen(strchr(optarg, ':')));
                printf("d arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
                printf("%s\n", logoption.lo_addr);
                port = strrchr(optarg, ':');
                printf("%d\n", atoi(++port));
                break;
            }
            case 'e':{
                printf("e arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
                break;
            }
            default: printf("Usage: \n");break;
        }
    }

    return 0;
}
