#include "../src/mplib/mpmod.h"

int main(int ac, char *av[])
{
    char buf[MP_MAXLINE];
    int clifd;
    struct sockaddr_un cliaddr;

    if((clifd = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1)
        mpExit("socket error");

    memset(&cliaddr, 0, sizeof(cliaddr));
    cliaddr.sun_family = AF_LOCAL;
    strcpy(cliaddr.sun_path, "/tmp/mcsg/local.socket");
    
    if(connect(clifd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)))
        mpExit("can not connect to server");
    
    memset(buf, 0, sizeof(buf));

    printf("enter data to send: ");
    while(fgets(buf, MP_MAXLINE, stdin) != NULL){
        buf[strlen(buf)-1] = 0;
        mpWrite(clifd, buf, sizeof(buf));
        printf("enter data to send: ");
    }
}
