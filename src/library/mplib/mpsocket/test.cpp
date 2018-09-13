#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>
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

// #include <regex>

#include "mpserversocket.h"
#include "mpservicesocket.h"

int main(int argc, char *argv[])
{
    // std::string str("192.168.1.147:");
    // std::regex rgx("((25[0-5]|2[0-4]\\d|[0-1]?\\d\\d?)($|(?!\\.$)\\.)){4}");
    // std::smatch res;

    // if(!std::regex_search(str, res, rgx))
    //     std::cout << "res.str() null" << std::endl;
    // else
    //     std::cout << "res.str() valid" << std::endl;

    // std::cout << res.str(1) << std::endl;
    // std::cout << res.str(2) << std::endl;
    // std::cout << res.str(3) << std::endl;
    // std::cout << res.str(4) << std::endl;
    // std::cout << res.str(5) << std::endl;

    int fd, n;
    char data[4096];
    char str[] = "msfdkm\n";
    FILE *fp, *fp1;

    fd = open("testfile", O_RDWR);

    if((fp = fdopen(fd, "r")) == NULL){
        perror("fdopen error");
        return -1;
    }
    if((fp1 = fdopen(fd, "w")) == NULL){
        perror("fdopen error");
        return -1;
    }
    close(fd);

    // if(fputs(str, fp1) < 0)
    //     perror("fputs");

    // while(fgets(data, 4096, fp)){
    //     std::cout << data;
    // }

    if((n = fread(data, 4096, 1, fp)) >= 0)
        std::cout << data << std::endl;
    else
        perror("fread");
    perror("fread");
    printf("%d\n", n);
    // MPServerSocket svr(4001);
    // MPServiceSocket ser;

    // svr.setBlock();
    // ser = 2;
    // if(ser)
    //     std::cout << "ser" << std::endl;
    // else
    //     std::cout << "!ser" << std::endl;

    // if(ser = svr.Accept())
    //     perror("accept");
    // else
    //     std::cout << "accept" << std::endl;

    // while(1) {
        
    // }

    // int clientfd, fdFlag;
    // FILE *clifp;
    // char data[4096];

    // fd_set rset;

    // MPServerSocket testsvr(4001);

    // MPSocket<struct sockaddr_in> sock;
    
    // if(!testsvr.isInvalid())
    //     std::cout << "inited" << std::endl;


    // if((clientfd = testsvr.acceptConnection()) < 0){
    //     std::cout << "accpet error" << std::endl;
    //     testsvr.Close();
    // }

    // if((fdFlag = fcntl(clientfd, F_GETFL, 0)) < 0)
    //     return -1;
    // if(fcntl(clientfd, F_SETFL, fdFlag|O_NONBLOCK) < 0)
    //     return -1;

    // if((clifp = fdopen(clientfd, "r")) == NULL){
    //     perror("fdopen error");
    //     return -1;
    // }

    // setbuf(clifp, NULL);

    // FD_ZERO(&rset);
    // FD_SET(clientfd, &rset);
    
    // for(;;){
    //     select(clientfd+1, &rset, NULL, NULL, NULL);
    //     std::cout << "server running" << std::endl;

    //     if(read(clientfd, data, 4096) != 0){
    //         std::cout << "server rcv: \n" << data << std::endl;
    //     } else {
    //         fclose(clifp);
    //         FD_CLR(clientfd, &rset);
    //     }

    //     // if((c = fgetc(clifp)) != EOF){
    //     //     std::cout << c;
    //     // } else {
    //     //     fclose(clifp);
    //     //     FD_CLR(clientfd, &rset);
    //     // }

    //     // while(std::fgets(data, 4096, clifp) != NULL){
    //     //     std::cout << "server rcv: " << data << std::endl;
    //     // }

    //     // while(fread(data, 4096, 1, clifp) != 0){
    //     //     std::cout << "server rcv: " << data << std::endl;
    //     //     // fflush(clifp);
    //     // }
    // }
    
    return 0;
}
