#include "control.h"
#include "../../json/rapidjson/document.h"

using namespace rapidjson;

int main(int argc, char *argv[])
{
    int i = 0;

    IoControl *fsw = new IoControl("fsw1");

    while(1) {
        ++i;
        sleep(2);
        if(i > 5)
            break;
        fsw->execute("pri");
        sleep(2);
        fsw->execute("res");
    }

    return 0;
}
