// #include "mpsocket.h"

/**
 * interfaces of MPSocket.
 */
// template <class Address>
// MPSocket<Address>::MPSocket(/* args */)
// {
// }

// template <class Address>
// MPSocket<Address>::~MPSocket()
// {
// }

// // template <class Address>
// // MPSocket<class Address>::StdSize MPSocket<Address>::operator << (const char *buffer)
// // {
// //     return fread(buffer, size, 1, this->inStream);
// // }

// // template <class Address>
// // MPSocket<Address>::StdSize MPSocket<Address>::operator >> (char *buffer)
// // {
// //     return fwrite(buffer, size, 1, this->outStream);
// // }

// template <class Address>
// typename MPSocket<Address>::StdSize MPSocket<Address>::Read(char *buffer, MPSocket<Address>::StdSize size)
// {
//     return fread(buffer, size, 1, this->inStream);
// }

// template <class Address>
// typename MPSocket<Address>::StdSize MPSocket<Address>::Write(const char *buffer, MPSocket<Address>::StdSize size)
// {
//     return fwrite(buffer, size, 1, this->outStream);
// }

// template <class Address>
// int MPSocket<Address>::Close()
// {
//     return close(this->sockfd);
// }

// template <class Address>
// bool MPSocket<Address>::shutdownRDWR()
// {
//     return shutdown(this->sockfd, SHUT_RDWR);
// }

// template <class Address>
// bool MPSocket<Address>::shutdownRead()
// {
//     return shutdown(this->sockfd, SHUT_RD);
// }

// template <class Address>
// bool MPSocket<Address>::shutdownWrite()
// {
//     return shutdown(this->sockfd, SHUT_WR);
// }

// template <class Address>
// bool MPSocket<Address>::openInStream()
// {
//     if((this->inStream = fdopen(this->sockfd, "r")) == NULL)
//         return false;
//     return true;
// }

// template <class Address>
// bool MPSocket<Address>::openOutStream()
// {
//     if((this->outStream = fdopen(this->sockfd, "w")) == NULL)
//         return false;
//     return true;
// }

// template <class Address>
// bool MPSocket<Address>::closeInStream()
// {
//     return fclose(this->inStream);
// }

// template <class Address>
// bool MPSocket<Address>::closeOutStream()
// {
//     return fclose(this->outStream);
// }

// template <class Address>
// bool MPSocket<Address>::isInvalid() const
// {
//     if(this->sockfd < 0)
//         return false;
//     return true;
// }

// template <class Address>
// template <typename Option>
// int MPSocket<Address>::setSocket(int key, Option option)
// {
//     return setsockopt(this->sockfd, SOL_SOCKET, key, &option, sizeof(option));
// }

// template <class Address>
// template <typename Option>
// int MPSocket<Address>::getSocketOption(int key, Option option)
// {
//     return getsockopt(this->sockfd, SOL_SOCKET, key, &option, sizeof(option));
// }

// template <class Address>
// template <typename Addr>
// int MPSocket<Address>::getPeerName(Sock peer, Addr addr)
// {
//     return getpeername(peer, &addr, sizeof(addr));
// }

// template <class Address>
// typename MPSocket<Address>::Sock MPSocket<Address>::getDescriptor() const
// {
//     return this->sockfd;
// }
