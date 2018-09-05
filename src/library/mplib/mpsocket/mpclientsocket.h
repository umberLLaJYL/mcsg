#ifndef _MPCLIENTSOCKET_H
#define _MPCLIENTSOCKET_H

#include "mpsocket.h"

/**
 * Derived class: MPServerSocket, which inherit from MPSocket.
 */
class MPClientSocket : public MPSocket<struct sockaddr_in> {

private:

public:
    MPClientSocket() = default;
    ~MPClientSocket();

    bool reopen() override;
    template <typename ADDR>
    bool rebind(ADDR);
    bool relisten(int);

    Sock acceptConnection();
    Sock acceptConnection(struct sockaddr_in, socklen_t *len);

    int getBacklog() const;
};

#include "mpclientsocket.cpp"

#endif
