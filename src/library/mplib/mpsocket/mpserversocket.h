#ifndef _MPSERVERSOCKET_H
#define _MPSERVERSOCKET_H

#include "mpsocket.h"

/**
 * Derived class: MPServerSocket, which inherit from MPSocket.
 */
class MPServerSocket : public _MPServerSocket<struct sockaddr_in> {

    typedef int Port;

private:
    Port port;

public:
    MPServerSocket() = default;
    MPServerSocket(Port lp) : port(lp) {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl(INADDR_ANY);
        address.sin_port = htons(port);
        
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        openInStream();
        openOutStream();
        int enable = 1;
        setSocket(SO_REUSEADDR, enable);
        enable = 1;
        setSocket(SO_KEEPALIVE, enable);

        setNonblock();

        Bind();
        Listen();
    }
    ~MPServerSocket() {}

    bool reopen() {
        Close();
        if((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
            return false;
        return true;
    }

    bool setAddress(const char *localAddress) {
        address.sin_family = AF_INET;
        address.sin_port = htons(port);

        if(inet_pton(AF_INET, localAddress, (void *)&address.sin_addr.s_addr) != 1)
            return false;
        return true;
    }
    void setAddress(in_addr_t localAddress) {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = localAddress;
        address.sin_port = htons(port);
    }
    
    void setPort(Port lp){
        port = lp;
    }

    bool Bind() {
        return _bind(address);
    }
};

#endif
