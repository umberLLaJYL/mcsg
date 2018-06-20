#ifndef _UART_H
#define _UART_H

#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>

extern int uartInitialize(const char *tty, int speed, int databit, char parity, int stopbit);

#endif
