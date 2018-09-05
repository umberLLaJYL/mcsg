#ifndef _MPSERVERSOCKET_H
#define _MPSERVERSOCKET_H

#include "mpsocket.h"

/**
 * Derived class: MPServerSocket, which inherit from MPSocket.
 */
class MPServerSocket : public MPSocket<struct sockaddr_in> {

    typedef int Port;

private:
    Port port;
    int basklog;

public:
    MPServerSocket() = default;
    MPServerSocket(Port);
    ~MPServerSocket();

    bool reopen() override;
    template <typename ADDR>
    bool rebind(ADDR);
    bool relisten(int);

    Sock acceptConnection();
    Sock acceptConnection(struct sockaddr_in, socklen_t *len);

    int getBacklog() const;
};

#include "mpserversocket.cpp"

#endif
