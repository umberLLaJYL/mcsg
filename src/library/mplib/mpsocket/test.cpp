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

#include "mpserversocket.h"

int main(int argc, char *argv[])
{
    int sockfd, client[10], clientfd, enable = 1, fdFlag;
    FILE *clifp;
    char data[4096], c;

    fd_set rset;

    MPServerSocket testsvr(4001);
    
    if(!testsvr.isInvalid())
        std::cout << "inited" << std::endl;

    if((clientfd = testsvr.acceptConnection()) < 0){
        std::cout << "accpet error" << std::endl;
        testsvr.Close();
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
    
    return 0;
}
