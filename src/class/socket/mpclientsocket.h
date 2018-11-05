#ifndef _MPCLIENTSOCKET_H
#define _MPCLIENTSOCKET_H

#include "mpsocket.h"

/**
 * Derived class: MPServerSocket, which inherit from MPSocket.
 */
class MPClientSocket : public _MPClientSocket<struct sockaddr_in> {

    typedef int Port;

private:
    Port port;

public:
    MPClientSocket() = default;
    MPClientSocket(Port cp, const char *dest) : port(cp) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        setDestination(cp, dest);
        Connect();
    }
    MPClientSocket(Port cp, in_addr_t dest) : port(cp) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        setDestination(cp, dest);
        Connect();
    }
    MPClientSocket(const StdString &dest) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        setDestination(dest);
        Connect();
    }
    ~MPClientSocket();

    bool reopen() {
        Close();

        if((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
            return false;
        return true;
    }

    bool setDestination(Port cp, const char *dest) {
        port = cp;
        destination.sin_family = AF_INET;
        destination.sin_port = htons(port);

        if(inet_pton(AF_INET, dest, (void *)&destination.sin_addr.s_addr) != 1)
            return false;
        return true;
    }
    void setDestination(Port cp, in_addr_t dest) {
        port = cp;
        destination.sin_family = AF_INET;
        destination.sin_addr.s_addr = dest;
        destination.sin_port = htons(port);
    }
    void setDestination(const StdString &dest) {

    }
};

#endif
