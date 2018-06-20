#include "uart.h"

extern int uartInitialize(const char *tty, int speed, int databit, char parity, int stopbit)
{
    int ttyFD;
    int baudrata;
    struct termios option;

    if((ttyFD = open(tty, O_RDWR|O_NOCTTY)) < 0)
        return -1;
    memset(&option, 0, sizeof(struct termios));
    option.c_cflag |= (CLOCAL|CREAD);
    option.c_cflag &= ~CSIZE;

    switch(speed){
        case 1200:  baudrata = B1200;   break;
        case 2400:  baudrata = B2400;   break;
        case 4800:  baudrata = B4800;   break;
        case 9600:  baudrata = B9600;   break;
        case 19200: baudrata = B19200;  break;
        case 38400: baudrata = B38400;  break;
        case 57600: baudrata = B57600;  break;
        case 115200:
        default:    baudrata = B115200; break;
    }
    cfsetispeed(&option, speed);
    cfsetospeed(&option, speed);

    switch(databit){
        case 5:  option.c_cflag |= CS5;
        case 6:  option.c_cflag |= CS6;
        case 7:  option.c_cflag |= CS7;
        case 8:
        default: option.c_cflag |= CS8;
    }

    switch(parity){
        default:
        case 'n':
        case 'N':
            option.c_cflag &= ~PARENB;
            option.c_iflag &= ~INPCK;
            break;
        case 'o':
        case 'O':
            option.c_cflag |= (PARENB|PARODD);
            option.c_iflag |= INPCK;
            break;
        case 'e':
        case 'E':
            option.c_cflag |= PARENB;
            option.c_iflag &= ~PARODD;
            option.c_cflag |= INPCK;
            break;
    }

    switch(stopbit){
        default:
        case 1: option.c_cflag &= ~CSTOPB; break;
        case 2: option.c_cflag |=  CSTOPB; break;
    }
    option.c_cc[VTIME] = 0;
    option.c_cc[VMIN] = 1;

    if(tcsetattr(ttyFD, TCSANOW, &option))
        return -1;
    return ttyFD;
}
