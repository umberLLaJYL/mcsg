#include "control.h"

using namespace rapidjson;

int main(int argc, char *argv[])
{
    int i = 0;

    Control fsw("fsw11");

    // while(1) {
    //     ++i;
    //     sleep(2);
    //     if(i > 5)
    //         break;
    //     fsw.execute("seq-pri");
    //     printf("0x%04x\n", fsw["ready"]);
    //     sleep(2);
    //     fsw.execute("seq-res");
    //     printf("0x%04x\n", fsw["ready"]);
    // }

    return 0;
}
