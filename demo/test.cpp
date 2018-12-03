#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

#include <string.h>
#include <ostream>
#include <iostream>

int main(int argc, char const *argv[])
{
    DIR *dir = opendir(".");
    if(dir == NULL)
        perror("opendir");

    struct dirent *cont;
    while((cont = readdir(dir)) != NULL) {
        if(strcmp(cont->d_name, ".") == 0 || strcmp(cont->d_name, "..") == 0)
            continue;
        else {
            printf("%s: %d\n", cont->d_name, cont->d_type);
        }
    }

    return 0;
}
