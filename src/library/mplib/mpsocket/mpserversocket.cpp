#include "mpserversocket.h"

/**
 * implementation: MPServerSocket
 */
MPServerSocket::MPServerSocket(Port lp) : port(lp),
                                          basklog(8)
{
    int enable = 1;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    openInStream();
    openOutStream();

    setSocket(SO_REUSEADDR, enable);
    setSocket(SO_KEEPALIVE, enable);

    rebind(address);
    relisten(basklog);
}

MPServerSocket::~MPServerSocket()
{
}

bool MPServerSocket::reopen()
{
    if((this->sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
        return false;
    return true;
}

template <typename ADDR>
bool MPServerSocket::rebind(ADDR serverAddress)
{
    return bind(this->sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
}

bool MPServerSocket::relisten(int bl)
{
    return listen(this->sockfd, bl);
}

MPSocket<struct sockaddr_in>::Sock MPServerSocket::acceptConnection()
{
    return accept(this->sockfd, (struct sockaddr *)NULL, NULL);
}
MPSocket<struct sockaddr_in>::Sock MPServerSocket::acceptConnection(struct sockaddr_in addr, socklen_t *len)
{
    return accept(this->sockfd, (struct sockaddr *)&addr, len);
}

int MPServerSocket::getBacklog() const
{
    return this->basklog;
}
