// #include "GPIOController.h"
#include "test.h"

#include <dlfcn.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include <memory>


class MrcFactory {
private:
    /* data */
public:
    MrcFactory() {

    }
    ~MrcFactory() {

    }

    template<class ProductType>
    ProductType create(const std::string &idx) {
        
    }
};

std::shared_ptr<Test> (*getTestdl)();
std::shared_ptr<Test> (*getTestSo)();

int main(int argc, char const *argv[])
{
    // if(argv[1] == NULL)
    //     return 1;

    void *handle = dlopen("/usr/lib/libfunc.so", RTLD_LAZY);
    if(handle == NULL)
        perror("dlopen");
        
    getTestSo = (std::shared_ptr<Test> (*)())dlsym(handle, "_Z9getObjectv");

    const char *dlmsg = dlerror();
    if(dlmsg != NULL) {
        printf("dlsym: %s\n", dlmsg);
        dlclose(handle);
        return 1;
    }
    dlclose(handle);


    std::shared_ptr<Test> classSo = getTestSo();

    classSo->show("njknkjnknknkn");

    // getTestdl1 = (std::shared_ptr<Test> (*)())dlsym(handle, "getSobject");

    // const char *dlmsg1 = dlerror();
    // if(dlmsg1 != NULL) {
    //     printf("dlsym: %s\n", dlmsg1);
    //     dlclose(handle);
    //     return 1;
    // }
    // std::shared_ptr<Test> ctest1 = getTestdl1();

    // ctest1->show("fsgsfgs");


    return 0;
}
