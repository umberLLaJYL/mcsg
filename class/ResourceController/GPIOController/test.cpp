// #include "GPIOController.h"
// #include "test.h"

// #include <dlfcn.h>

#include <unistd.h>
#include <fcntl.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <ostream>

int main(int argc, char const *argv[])
{
    char buf1[4096], buf2[4096];

    int fd1 = open("./test.json", O_RDONLY);
    int fd2 = dup(fd1);

    read(fd1, buf1, 4096);
    std::cout << "fd1: " << buf1 << std::endl;

    lseek(fd2, 0, SEEK_SET);
    close(fd1);

    if(read(fd2, buf2, 4096) <= 0)
        perror("fd2");
    else
        std::cout << "fd2: " << buf2 << std::endl;

    return 0;
}
