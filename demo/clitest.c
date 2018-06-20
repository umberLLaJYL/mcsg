#include "../src/mplib/mpmod.h"

int main(int ac, char *av[])
{
    char stdinBuf[MP_MAXLINE], tcpBuf[MP_MAXLINE];
    int clientFD;
    struct sockaddr_in clientAddr;
    fd_set readSet;

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
    
    memset(stdinBuf, 0, sizeof(stdinBuf));
    if(mpWrite(clientFD, "{\"type\":\"sync\",\"substance\":{}}", sizeof(stdinBuf)) < 0)
        mpExit("can not sync with server");

    printf("waiting for ack from server...\n");
    if(mpRead(clientFD, stdinBuf, sizeof(stdinBuf)) <= 0)
        mpExit("can not get ack from server");
    printf("client initialized.\n");
    FD_ZERO(&readSet);

    printf("enter data to send: ");
    for(;;){
        FD_SET(STDIN_FILENO, &readSet);
        FD_SET(clientFD, &readSet);
        if(select(clientFD+1, &readSet, NULL, NULL, NULL) < 0){
            if(errno == EINTR)
                continue;
            else
                return ESVRWAIT;
        }
        if(FD_ISSET(STDIN_FILENO, &readSet)){
            fgets(stdinBuf, sizeof(stdinBuf), stdin);
            stdinBuf[strlen(stdinBuf)-1] = 0;
            mpWrite(clientFD, stdinBuf, sizeof(stdinBuf));
        }
        if(FD_ISSET(clientFD, &readSet)){
            if(mpRead(clientFD, tcpBuf, sizeof(tcpBuf)) == 0)
                exit(0);
            printf("client rcv: %s\n", tcpBuf);
        }
    }
}
