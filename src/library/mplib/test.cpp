#include "mplib.h"
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdarg.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <sys/wait.h>
// #include <errno.h>
// #include <stdint.h>
// #include <fcntl.h>
// #include <time.h>
// #include <sys/resource.h>
// #include <signal.h>
// #include <getopt.h>

// #include <pthread.h>

// #include <iostream>
// #include <string>
// #include <vector>
// #include <cstddef>
// #include <thread>
// #include <map>

int main(int argc, char *argv[])
{
    // int fd, fd1, i;
    // std::string str("rising");
    // char buf[8] = {0};

    // fd = open("/sys/class/gpio/gpio64/edge", O_RDONLY);

    // if((i = write(fd, str.c_str(), 8)) < 0)
    //     perror("write");
 
    // if((i = read(fd, buf, 8)) < 0)
    //     perror("read");
    // printf("ret: %d\n", i);

    // str.assign(buf);

    // if(str == "none\n")
    //     printf("dsdsd]n\n");
    
    GPIO *io36 = new GPIO(64);

    io36->output();

    while(1) {
        sleep(1);
        if(io36->getDirection() == 1)
            std::cout << "io out" << std::endl;
        else if(io36->getDirection() == 0)
            std::cout << "io in" << std::endl;
        else if(io36->getDirection() == -1)
            std::cout << "error" << std::endl;

        // sleep(1);
        // io36->pullUp();
        // sleep(1);
        // io36->pullDown();
    }

    delete io36;
    
    return 0;
}
