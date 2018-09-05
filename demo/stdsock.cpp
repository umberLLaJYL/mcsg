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
#include <string>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    int sockfd, client[10], clientfd, enable = 1, fdFlag;
    FILE *clifp;
    struct sockaddr_in serverAddress = {0};
    char data[4096], c;

    fd_set rset;

    std::string ifdata;

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(4001);

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket error");
        return -1;
    }

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable))){
        perror("setsockopt error");
        return -1;
    }

    if(bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in))){
        perror("bind error");
        return -1;
    }

    if(listen(sockfd, 8)){
        perror("listen error");
        return -1;
    }

acpt:
    if((clientfd = accept(sockfd, (struct sockaddr *)NULL, NULL)) < 0){
        if(errno == EINTR)
            goto acpt;
        else
            return -1;
    }

    if((fdFlag = fcntl(clientfd, F_GETFL, 0)) < 0)
        return -1;
    if(fcntl(clientfd, F_SETFL, fdFlag|O_NONBLOCK) < 0)
        return -1;

    if((clifp = fdopen(clientfd, "r")) == NULL){
        perror("fdopen error");
        return -1;
    }

    setbuf(clifp, NULL);

    FD_ZERO(&rset);
    FD_SET(clientfd, &rset);
    
    for(;;){
        select(clientfd+1, &rset, NULL, NULL, NULL);
        std::cout << "server running" << std::endl;

        if(read(clientfd, data, 4096) != 0){
            std::cout << "server rcv: \n" << data << std::endl;
        } else {
            fclose(clifp);
            FD_CLR(clientfd, &rset);
        }

        // if((c = fgetc(clifp)) != EOF){
        //     std::cout << c;
        // } else {
        //     fclose(clifp);
        //     FD_CLR(clientfd, &rset);
        // }

        // while(std::fgets(data, 4096, clifp) != NULL){
        //     std::cout << "server rcv: " << data << std::endl;
        // }

        // while(fread(data, 4096, 1, clifp) != 0){
        //     std::cout << "server rcv: " << data << std::endl;
        //     // fflush(clifp);
        // }
    }

    printf("close\n");

    // max = sockfd + 1;
    // FD_ZERO(&grpSet);
    // FD_SET(sockfd, &grpSet);

    // if((fdFlag = fcntl(sockfd, F_GETFL, 0)) < 0)
    //     return -1;
    // if(fcntl(sockfd, F_SETFL, fdFlag|O_NONBLOCK) < 0)
    //     return -1;





    // for(;;){

    // }

    return 0;
}
