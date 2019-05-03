#include "socket.h"

Socket::Socket()
{

}

Socket::Socket(int family, int type, int protocol)
{
    int n;

    if((n = socket(family, type, protocol)) < 0)
    {
        /*....*/
        throw "socket error";
    }

    sock_fd = n;
}

void Socket::Bind(SockAddr *sa)
{
    if(bind(sock_fd, sa->getSockAddr(), sa->size()) < 0)
    {
        /*....*/
        throw "bind error";
    }
}

void Socket::Connect(SockAddr *sa)
{
    if(connect(sock_fd, sa->getSockAddr(), sa->size()) < 0)
    {
        /*....*/
        throw "connect error";
    }
}

void Socket::Listen(int backlog)
{
    char *ptr;

    if((ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if(listen(sock_fd, backlog) < 0)
    {
        /*....*/
        throw "listen error";
    }
}

Socket Socket::Accept(SockAddr *sa)
{
    int n;
    Socket sock;
    struct sockaddr _sa;
    socklen_t lenght;

    if((n = accept(sock_fd, &_sa, &lenght)) < 0)
    {
        /*.....*/
        throw "accept error";
    }

    sock.sock_fd = n;
    sa = new SockAddr((struct sockaddr_in*)&_sa, lenght);

    return sock;
}

void Socket::Close()
{
    close(sock_fd);
}
