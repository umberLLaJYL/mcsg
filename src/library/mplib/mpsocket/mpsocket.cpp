#ifndef _MPSOCKET_CPP
#define _MPSOCKET_CPP

#include "mpsocket.h"

_MPSocket::_MPSocket() : sockfd(-1), inStream(NULL), outStream(NULL)
{
}

_MPSocket::~_MPSocket()
{
    this->Close();
}


_MPSocket::operator bool() const
{
    if(this->sockfd < 0)
        return false;
    else
        return true;
}

_MPSocket &_MPSocket::operator = (Sock sock)
 {
    this->Close();
    this->sockfd = sock;
    return *this;
}

_MPSocket::StdSize _MPSocket::Read(char *buffer, StdSize size)
{
    return fread(buffer, size, 1, this->inStream);
}

_MPSocket::StdSize _MPSocket::Write(const char *buffer, StdSize size)
{
    return fwrite(buffer, size, 1, this->outStream);
}

bool _MPSocket::Close()
{
    closeInStream();
    closeOutStream();
    return close(this->sockfd);
}

bool _MPSocket::shutdownRDWR()
{
    return shutdown(this->sockfd, SHUT_RDWR);
}

bool _MPSocket::shutdownRead()
{
    return shutdown(this->sockfd, SHUT_RD);
}

bool _MPSocket::shutdownWrite()
{
    return shutdown(this->sockfd, SHUT_WR);
}

bool _MPSocket::openInStream()
{
    if((this->inStream = fdopen(this->sockfd, "r")) == NULL)
        return false;
    return true;
}

bool _MPSocket::openOutStream()
{
    if((this->outStream = fdopen(this->sockfd, "w")) == NULL)
        return false;
    return true;
}

bool _MPSocket::closeInStream()
{
    if(this->inStream)
        return fclose(this->inStream);
    return true;
}

bool _MPSocket::closeOutStream()
{
    if(this->outStream)
        return fclose(this->outStream);
    return true;
}

bool _MPSocket::isInvalid() const
{
    if(this->sockfd < 0)
        return true;
    return false;
}

template <typename Option>
bool _MPSocket::setSocket(int key, Option option)
{
    return setsockopt(this->sockfd, SOL_SOCKET, key, &option, sizeof(option));
}

bool _MPSocket::setNonblock()
{
    int fdFlag;

    if((fdFlag = fcntl(this->sockfd, F_GETFL, 0)) < 0)
        return false;
    if(fcntl(this->sockfd, F_SETFL, fdFlag|O_NONBLOCK) < 0)
        return false;
    return true;
}

bool _MPSocket::setBlock()
{
    int fdFlag;

    if((fdFlag = fcntl(this->sockfd, F_GETFL, 0)) < 0)
        return false;
    if(fcntl(this->sockfd, F_SETFL, fdFlag&(~O_NONBLOCK)) < 0)
        return false;
    return true;
}

template <typename Option>
bool _MPSocket::getSocketOption(int key, Option option) const
{
    return getsockopt(this->sockfd, SOL_SOCKET, key, &option, sizeof(option));
}

_MPSocket::Sock _MPSocket::getDescriptor() const
{
    return this->sockfd;
}

#endif
