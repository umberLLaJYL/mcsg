#ifndef _MPSERVICESOCKET_H
#define _MPSERVICESOCKET_H

#include "mpsocket.h"

/**
 * Derived class: MPServerSocket, which inherit from MPSocket.
 */
class MPServiceSocket : public _MPServiceSocket<struct sockaddr_in> {

private:

public:
    MPServiceSocket() = default;
    ~MPServiceSocket() {}

    using _MPSocket::operator =;
};

#endif
