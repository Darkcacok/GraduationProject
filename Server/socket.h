#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h> /* basic system data types */
#include <sys/socket.h> /* basic socket defns */
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <stdlib.h>
#include <unistd.h>


#include "sockaddr.h"

class Socket
{
public:
    Socket();
    Socket(int family, int type, int protocol);
    void Bind(SockAddr *sa);
    void Connect(SockAddr *sa);
    void Listen(int backlog);
    Socket Accept(SockAddr *sa);
    void Close();


private:
    int sock_fd;
};

#endif // SOCKET_H
