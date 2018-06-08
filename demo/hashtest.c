#include "../src/commons/mplib.h"
#include "../src/commons/mpmsg.h"

int main(int ac, char *av[])
{
    _FD fd;
    char buf[MP_MAXLINE], buf1[MP_MAXLINE];
    int32_t hashRes;

    

    fd = mpOpenJS("./bin/.devinfo.json", O_RDONLY);
    if(mpRead(fd, buf1, sizeof(buf)) == 0)
        mpExit("test error");
    printf("%s", buf1);
    mpCloseJS(fd);

    while(fgets(buf, MP_MAXLINE, stdin) != NULL){
        buf[strlen(buf)-1] = 0;
        MurmurHash3_x86_32(buf, strlen(buf), MP_MSGSEED, &hashRes);
        printf("hash: 0x%08x\n", hashRes);
    }
    exit(1);
}
