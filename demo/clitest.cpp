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

#include <sys/un.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <vector>
#include <cstddef>
// using namespace std;
#include <string>
#include <iostream>
#include <fstream>

int main(int ac, char *av[])
{
    char stdinBuf[4096], tcpBuf[4096];
    int clientFD, wlen;
    struct sockaddr_in clientAddr;
    fd_set readSet;
    FILE *sockfp;

    if(ac != 3){
        printf("args error");
        return -1;
    }

    if((clientFD = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket error");
        return -1;
    }

    if((sockfp = fdopen(clientFD, "w")) == NULL){
        perror("fdopen error");
        return -1;
    }

    memset(&clientAddr, 0, sizeof(struct sockaddr_in));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(atoi(av[2]));
    inet_pton(AF_INET, av[1], &clientAddr.sin_addr);
    
    if(connect(clientFD, (struct sockaddr *)&clientAddr, sizeof(clientAddr))){
        perror("connect error");
        return -1;
    }

    FD_ZERO(&readSet);

    std::cout << "enter data to send: " << std::endl;

    for(;;){
        FD_SET(STDIN_FILENO, &readSet);
        FD_SET(clientFD, &readSet);

        if(select(clientFD+1, &readSet, NULL, NULL, NULL) < 0){
            if(errno == EINTR)
                continue;
            else
                return -1;
        }

        if(FD_ISSET(STDIN_FILENO, &readSet)){
            fgets(stdinBuf, sizeof(stdinBuf), stdin);
            stdinBuf[strlen(stdinBuf)] = 0;

            std::cout << "stdin rcv: " << stdinBuf;

            if((wlen = fputs(stdinBuf, sockfp)) != EOF)
                printf("fwrite len: %d\n", wlen);
            fflush(sockfp);
            std::cout << "enter data to send: " << std::endl;
        }

        // if(FD_ISSET(clientFD, &readSet)){
        //     if(fread(stdinBuf, sizeof(stdinBuf), 1, sockfp) == 0)
        //         exit(0);
        //     printf("client rcv: %s\n", tcpBuf);
        // }
    }
}
