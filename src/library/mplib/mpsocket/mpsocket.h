#ifndef _MPSOCKET_H
#define _MPSOCKET_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <vector>
#include <cstddef>
#include <fstream>

/**
 * Abstract base class template: MPSocket.
 */
template <class Address>
struct MPSocket {

    typedef int Sock;
    typedef std::size_t StdSize;
    typedef std::string StdString;

private:
    FILE *inStream;
    FILE *outStream;

    StdString inBuffer;
    StdString outBuffer;

protected:
    Address address;
    Sock sockfd;

public:
    MPSocket();
    ~MPSocket();

    // struct MPSocket &operator << (const char *);
    // struct MPSocket &operator >> (char *);

    virtual bool reopen() = 0;

    StdSize Read(char *buffer, StdSize size);
    StdSize Write(const char *buffer, MPSocket<Address>::StdSize size);
    int Close();

    bool shutdownRDWR();
    bool shutdownRead();
    bool shutdownWrite();

    bool openInStream();
    bool openOutStream();

    bool closeInStream();
    bool closeOutStream();

    bool isInvalid() const;

    template <typename Option>
    int setSocket(int, Option);

    template <typename Option>
    int getSocketOption(int, Option);

    template <typename Addr>
    int getPeerName(Sock, Addr);

    Sock getDescriptor() const;
};

template <class Address>
MPSocket<Address>::MPSocket(/* args */)
{
}

template <class Address>
MPSocket<Address>::~MPSocket()
{
}

// template <class Address>
// MPSocket<class Address>::StdSize MPSocket<Address>::operator << (const char *buffer)
// {
//     return fread(buffer, size, 1, this->inStream);
// }

// template <class Address>
// MPSocket<Address>::StdSize MPSocket<Address>::operator >> (char *buffer)
// {
//     return fwrite(buffer, size, 1, this->outStream);
// }

template <class Address>
typename MPSocket<Address>::StdSize MPSocket<Address>::Read(char *buffer, MPSocket<Address>::StdSize size)
{
    return fread(buffer, size, 1, this->inStream);
}

template <class Address>
typename MPSocket<Address>::StdSize MPSocket<Address>::Write(const char *buffer, MPSocket<Address>::StdSize size)
{
    return fwrite(buffer, size, 1, this->outStream);
}

template <class Address>
int MPSocket<Address>::Close()
{
    return close(this->sockfd);
}

template <class Address>
bool MPSocket<Address>::shutdownRDWR()
{
    return shutdown(this->sockfd, SHUT_RDWR);
}

template <class Address>
bool MPSocket<Address>::shutdownRead()
{
    return shutdown(this->sockfd, SHUT_RD);
}

template <class Address>
bool MPSocket<Address>::shutdownWrite()
{
    return shutdown(this->sockfd, SHUT_WR);
}

template <class Address>
bool MPSocket<Address>::openInStream()
{
    if((this->inStream = fdopen(this->sockfd, "r")) == NULL)
        return false;
    return true;
}

template <class Address>
bool MPSocket<Address>::openOutStream()
{
    if((this->outStream = fdopen(this->sockfd, "w")) == NULL)
        return false;
    return true;
}

template <class Address>
bool MPSocket<Address>::closeInStream()
{
    return fclose(this->inStream);
}

template <class Address>
bool MPSocket<Address>::closeOutStream()
{
    return fclose(this->outStream);
}

template <class Address>
bool MPSocket<Address>::isInvalid() const
{
    if(this->sockfd < 0)
        return false;
    return true;
}

template <class Address>
template <typename Option>
int MPSocket<Address>::setSocket(int key, Option option)
{
    return setsockopt(this->sockfd, SOL_SOCKET, key, &option, sizeof(option));
}

template <class Address>
template <typename Option>
int MPSocket<Address>::getSocketOption(int key, Option option)
{
    return getsockopt(this->sockfd, SOL_SOCKET, key, &option, sizeof(option));
}

template <class Address>
template <typename Addr>
int MPSocket<Address>::getPeerName(Sock peer, Addr addr)
{
    return getpeername(peer, &addr, sizeof(addr));
}

template <class Address>
typename MPSocket<Address>::Sock MPSocket<Address>::getDescriptor() const
{
    return this->sockfd;
}

#endif
