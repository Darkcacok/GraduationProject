#include "sockaddr.h"

SockAddr::SockAddr()
{
    memset(&sa_in, 0, sizeof (sa_in));
    length = sizeof (sa_in);
}

SockAddr::SockAddr(int family, uint32_t addr, uint16_t port)
    :SockAddr()
{
    sa_in.sin_family = family;
    sa_in.sin_addr.s_addr = htonl(addr);
    sa_in.sin_port = htons(port);

    length = sizeof (sa_in); //????
}

SockAddr::SockAddr(sockaddr_in *sa_in, socklen_t lenght)
{
    if(sa_in == NULL)
    {
        /*....*/
        throw "error to create SockAddr";
    }
    memcpy(&this->sa_in, sa_in, lenght);
    this->length = lenght;
}

struct sockaddr *SockAddr::getSockAddr()
{
   struct sockaddr *sa = (struct sockaddr*)&sa_in;

   return sa;
}

socklen_t SockAddr::size()
{
    return length;
}
