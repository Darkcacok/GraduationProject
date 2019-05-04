#ifndef SOCKADDR_H
#define SOCKADDR_H

#include <sys/types.h> /* basic system data types */
#include <sys/socket.h> /* basic socket defns */
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>
#include <string.h>

class SockAddr
{
public:
    SockAddr();
    SockAddr(int family, uint32_t addr, uint16_t port);
    SockAddr(int family, const char *addr, uint16_t port);
    SockAddr(struct sockaddr_in *sa_in, socklen_t lenght);

    struct sockaddr *getSockAddr();
    socklen_t size();

private:
    struct sockaddr_in sa_in;
    socklen_t length;
};

#endif // SOCKADDR_H
