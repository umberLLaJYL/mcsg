#ifndef _MPSOCKET_H
#define _MPSOCKET_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <vector>
#include <cstddef>

// #include <regex>

struct _MPSocket {
    typedef int Sock;
    typedef std::size_t StdSize;
    typedef std::string StdString;

private:
    FILE *inStream;
    FILE *outStream;

    StdString inBuffer;
    StdString outBuffer;

protected:
    Sock sockfd;

public:
    _MPSocket();
    ~_MPSocket();

    explicit operator bool() const;

    StdSize Read(char *, StdSize);
    StdSize Write(const char *, StdSize);
    bool Close();

    bool shutdownRDWR();
    bool shutdownRead();
    bool shutdownWrite();

    bool openInStream();
    bool openOutStream();

    bool closeInStream();
    bool closeOutStream();

    bool isInvalid() const;

    template <typename Option>
    bool setSocket(int, Option);
    bool setNonblock();
    bool setBlock();

    template <typename Option>
    bool getSocketOption(int, Option) const;
    Sock getDescriptor() const;
};

/**
 * base class template: MPSocket.
 */
template <class Address>
struct _MPServerSocket : public _MPSocket {

private:
    int backlog;

protected:
    Address address;

    template <typename ADDR>
    bool _bind(ADDR serverAddress) {
        return !bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    }

    template <typename ADDR>
    void setAddress(ADDR serverAddress) {
        address = serverAddress;
    }
    
public:
    _MPServerSocket() : backlog(10) {}
    ~_MPServerSocket() {}

    bool Listen(){
        return !listen(sockfd, backlog);
    }
    
    Sock Accept() {
        return accept(sockfd, (struct sockaddr *)NULL, NULL);
    }
    Sock Accept(Address addr, socklen_t length) {
        length = sizeof(addr);

        return accept(sockfd, (struct sockaddr *)&addr, &length);
    }

    void setBacklog(int bl) {
        backlog = bl;
    }

    int getBacklog() const {
        return backlog;
    }
};

template <class Address>
struct _MPServiceSocket : public _MPSocket {

private:
    Address peer;

public:
    _MPServiceSocket() {}
    ~_MPServiceSocket() {}

    bool getPeerName() {
        return !getpeername(sockfd, (struct sockaddr *)&peer, sizeof(peer));
    }
};

template <class Address>
struct _MPClientSocket : public _MPSocket {

private:
    Address local;

protected:
    Address destination;

public:
    _MPClientSocket();
    ~_MPClientSocket();

    bool Connect() {
        !connect(sockfd, (struct sockaddr *)destination, sizeof(destination));
    }
};

#include "mpsocket.cpp"

#endif
