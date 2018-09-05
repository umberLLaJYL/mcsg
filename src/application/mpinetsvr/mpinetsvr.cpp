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

#include "../../library/mplib/mpsocket.h"

int main(int argc, char const *argv[])
{
    MPServerSocket mpinetsvr(atoi(argv[1]));
    // MPPoller pollingControler;

    // pollingControler.add(mpinetsvr.getDescriptor());

    while(1) {
        // pollingControler.wait();
    }

    return 0;
}

