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
// #include <pthread.h>
#include <getopt.h>

// #define container_of(ptr, type, member)({ \
//             const typeof(((type *)0)->member) *__mptr = (ptr); \
//             (type *)((char *)__mptr - offsetof(type, member)); \
//         })
// #define container_of(ptr, type, member) ({                      \
//         const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
//         (type *)( (char *)__mptr - __offsetof(type,member) );})

// #define new(obj, opt...) obj##test(obj,##opt)

struct logopt{
    char *cp;
    int lo_mode;
    int lo_port;
    off_t lo_size;
    char lo_addr[16];
    char lo_path[104];
};

int main(int argc, char *argv[])
{
    int i = 9, opt;
    char *port, *token;
    // struct logopt logoption, *teststr;
    // static struct option options[] = {
    //     {"default", 2, NULL, 'a'},
    //     {"tcponly", 2, NULL, 'b'}
    // };

    char str[] = "osw(0'-'$1R1, 1'+'$1R2, 2'*'$1R3)";

    if(strncmp(strtok(str, "("), "osw", 3) == 0){
        token = strtok(NULL, ")");
        token = strtok(token, ",");
        while(token != NULL){
            printf("%s, %d\n", token, atoi(token));
            token = strtok(NULL, ",");
        }
    }

    // printf("argc: %d\n", argc);

    // for(i = 0; i < argc; i++){
    //     printf("argv%i: %s\n", i, argv[i]);
    // }

    // while((opt = getopt_long(argc, argv, "cd:e::", options, NULL)) != -1){
    //     switch(opt){
    //         case 'a':{
    //             break;
    //         }
    //         case 'b':{
    //             printf("b arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
    //             break;
    //         }
    //         case 'c':{
    //             printf("c arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
    //             break;
    //         }
    //         case 'd':{
    //             strncpy(logoption.lo_addr, optarg, strlen(optarg) - strlen(strchr(optarg, ':')));
    //             printf("d arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
    //             printf("%s\n", logoption.lo_addr);
    //             port = strrchr(optarg, ':');
    //             printf("%d\n", atoi(++port));
    //             break;
    //         }
    //         case 'e':{
    //             printf("e arg: %s, ind: %d, opt: %d\n", optarg, optind, optopt);
    //             break;
    //         }
    //         default: printf("Usage: \n");break;
    //     }
    // }

    return 0;
}
