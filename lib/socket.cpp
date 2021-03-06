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
        printf("error %s\n", strerror(errno));
        throw "bind error";
    }
}

void Socket::Connect(SockAddr *sa)
{
    if(connect(sock_fd, sa->getSockAddr(), sa->size()) < 0)
    {
        /*....*/
        printf("error %s\n", strerror(errno));
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
        printf("error %s\n", strerror(errno));
        throw "listen error";
    }
}

Socket *Socket::Accept(SockAddr *sa)
{
    int n;
    Socket *sock = new Socket();
    struct sockaddr _sa;
    socklen_t lenght = NULL;

    memset(&_sa, 0, sizeof (_sa));

    again:
    if((n = accept(sock_fd, &_sa, &lenght)) < 0)
    {
        if(errno == ECONNABORTED)
        {
            printf("error %s. Trying again\n", strerror(errno));
            goto again;
        }
        else {
            printf("error %s\n", strerror(errno));
            throw "error accept";
        }
    }

    sock->sock_fd = n;
    sa = new SockAddr((struct sockaddr_in*)&_sa, lenght);

    return sock;
}

void Socket::Close()
{
    close(sock_fd);
}

int Socket::Read(char *buf, int length)
{
    int n = read(sock_fd, buf, length);

    if(n < 0)
    {
        printf("error %s\n", strerror(errno));
        throw "read error";
    }

    return n;
}

int Socket::Writen(char *buf, int length)
{
    int nleft;
    int nwritten;
    const char *ptr;

    ptr = buf;
    nleft = length;

    while(nleft > 0)
    {
        if((nwritten = write(sock_fd, ptr, nleft)) <= 0)
        {
            /*....*/
            printf("error %s\n", strerror(errno));
            return -1;
        }

        nleft -= nwritten;
        ptr +=nwritten;
    }

    return length;
}
