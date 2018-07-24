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

// #define container_of(ptr, type, member)({ \
//             const typeof(((type *)0)->member) *__mptr = (ptr); \
//             (type *)((char *)__mptr - offsetof(type, member)); \
//         })
// #define container_of(ptr, type, member) ({                      \
//         const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
//         (type *)( (char *)__mptr - __offsetof(type,member) );})

#define new(obj, opt...) obj##test(obj,##opt)

struct logopt{
    int lo_mode;
    int lo_port;
    off_t lo_size;
    char lo_addr[16];
    char lo_path[104];
};

int svrtest(int a, int b)
{
    printf("svr %d\n", a);
    printf("opt %d\n", b);
}

int sertest(int a, int b)
{
    printf("ser %d\n", a);
    printf("opt %d\n", b);
}

int svr = 9;
int ser = 8;

int main(int argc, char *argv[])
{
    pid_t pid;
    int i = 9, opt;
    char *port;
    struct logopt logoption, *teststr;
    static struct option options[] = {
        {"default", 2, NULL, 'a'},
        {"tcponly", 2, NULL, 'b'}
    };
    // printf("argc: %d\n", argc);

    // for(i = 0; i < argc; i++){
    //     printf("argv%i: %s\n", i, argv[i]);
    // }
    teststr = malloc(sizeof(struct logopt));
    // memset(teststr, 0, sizeof(teststr));
    teststr->lo_port = 0;
    if(&teststr->lo_port == NULL)
        printf("ddddd\n");

    if(argc == 2)
        new(svr, argc);
    else if(argc == 3)
        new(ser, argc);

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
