#include "../src/mplib/mpmod.h"
#include "../application/daemon/mplog.h"

int main(int ac, char *av[])
{
    char buf[MP_MAXLINE];

    mpOpenLog("MCSG", -1, 9);
    mpLog(LOG_NOTICE, "logtest %s", "tcp/udp login");
    mpLog(LOG_NOTICE, "logtest %s", "tcp/udp logout");

    return 0;
}
