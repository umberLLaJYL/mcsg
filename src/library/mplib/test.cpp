#include "mplib.h"

int main(int argc, char *argv[])
{
    int i = 0;
    GPIO *io36 = new GPIO(36);

    io36->output();

    while(1) {
        ++i;
        if(i > 5)
            break;
        sleep(1);
        io36->pullUp();
        sleep(1);
        io36->pullDown();
    }

    delete io36;
    
    return 0;
}
