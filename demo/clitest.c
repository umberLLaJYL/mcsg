#include "../src/mplib/mpmod.h"

int main(int ac, char *av[])
{
    char buf[MP_MAXLINE];
    int clientFD;
    struct sockaddr_in clientAddr;

    if(ac != 3)
        mpQuit(1, "Usage: [IP address] [port]\n");

    if((clientFD = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        mpExit("socket error");

    memset(&clientAddr, 0, sizeof(struct sockaddr_in));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(atoi(av[2]));
    inet_pton(AF_INET, av[1], &clientAddr.sin_addr);
    
    if(connect(clientFD, (struct sockaddr *)&clientAddr, sizeof(clientAddr)))
        mpExit("can not connect to server");
    
    memset(buf, 0, sizeof(buf));
    if(mpWrite(clientFD, "{\"type\":\"sync\",\"substance\":{}}", sizeof(buf)) < 0)
        mpExit("can not sync with server");

    printf("waiting for ack from server...\n");
    if(mpRead(clientFD, buf, sizeof(buf)) <= 0)
        mpExit("can not get ack from server");
    printf("client initialized.\n");

    printf("enter data to send: ");
    while(fgets(buf, MP_MAXLINE, stdin) != NULL){
        buf[strlen(buf)-1] = 0;
        mpWrite(clientFD, buf, sizeof(buf));
        printf("enter data to send: ");
    }
}
