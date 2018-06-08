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

#include <sys/wait.h>
#include <sys/un.h>
#include <stdint.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>

struct tcpheader{
    uint8_t th_verhl;
    uint8_t th_tos;
    uint16_t th_tlen;
    uint16_t th_id;
    uint16_t th_fragment;
    uint8_t th_ttl;
    uint8_t th_proto;
    uint16_t th_checksum;
    uint32_t th_oaddr;
    uint32_t th_daddr;
    char buf[4096];
};

int main(int argc, char const *argv[])
{
    int sockfd, len;
    struct sockaddr_in svraddr;
    struct tcpheader header;
    char oip[16], dip[16];


    sizeof(header);

    // if((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0)
        perror("socket");
    // svraddr.sin_family = AF_INET;
    // svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // svraddr.sin_port  = htons(4001);

    // if(bind(sockfd, (struct sockaddr *)&svraddr, sizeof(svraddr)))
    //     perror("bind");

    for(;;){
        if((len = read(sockfd, &header, sizeof(header))) <= 0)
            perror("read");
        // inet_ntop(AF_INET, &header.th_oaddr, oip, 16);
        // inet_ntop(AF_INET, &header.th_daddr, dip, 16);
        printf("len: %d, protocol: %d, oip: %s, dip: %s\n", len, header.th_proto, oip, dip);
    }
    
    return 0;
}

