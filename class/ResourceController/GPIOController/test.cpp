#include "ITest.h"

#include <dlfcn.h>

#include <unistd.h>
#include <fcntl.h>

// #include <stdexcept>

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <ostream>

int main(int argc, char const *argv[])
{
    void *handle = dlopen("./libtest.so", RTLD_NOW);
    if(handle == NULL) {
        printf("depoen: %s\n", dlerror());
        return 1;
    }

    ITest *ctest = (ITest *)dlsym(handle, "test_g");
    const char *dlmsg = dlerror();
    if(dlmsg != NULL) {
        printf("dlsym: %s\n", dlmsg);
        dlclose(handle);
        return 1;
    }
    dlclose(handle);

    ctest->show("svnlsjnvljsnlvfnzbgk");

    return 0;
}
