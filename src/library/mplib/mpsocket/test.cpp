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
    // sizeof(GPIO);
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

    // if((fexport = open("/sys/class/gpio/export", O_WRONLY)) < 0)
    //     perror("open");
    // if(write(fexport, "36", 8) < 0)
    //     perror("write");

    // if((fd1 = open("/sys/class/gpio/gpio36/value", O_WRONLY)) < 0)
    //     perror("open d");

    while(1) {
        // memset(c, 0, 8);
        // if((fd = open("/sys/class/gpio/gpio36/value", O_RDONLY)) < 0)
        //     perror("open d");

        // if(write(fd1, "1", 8) < 0)
        //     perror("write d");
        // if(read(fd, c, sizeof(c)) < 0)
        //     perror("read d");
        // printf("vlu: %s\n", c);

        // close(fd);
        // sleep(1);

        // if((fd = open("/sys/class/gpio/gpio36/value", O_RDONLY)) < 0)
        //     perror("open d");

        // if(write(fd1, "0", 8) < 0)
        //     perror("write d");
        // if(read(fd, c, sizeof(c)) < 0)
        //     perror("read d");
        // printf("vlu: %s\n", c);
        // close(fd);
    }

    // close(fd);

    // if((fd = open("/sys/class/gpio/gpio36/value", O_RDWR)) < 0)
    //     perror("open v");

    // MPServerSocket svr(4001);
    // MPServiceSocket ser;

    // svr.setBlock();
    // ser = -2;
    // if(ser)
    //     std::cout << "ser" << std::endl;
    // else
    //     std::cout << "!ser" << std::endl;

    // if(ser.Close() == false)
    //     perror("close");

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
