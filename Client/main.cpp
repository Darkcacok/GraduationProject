#include <iostream>

#include "../lib/socket.h"
#include "../lib/sockaddr.h"


void str_cli(Socket *sockfd)
{
    int MAXLINE = 1024;

    char sendline[MAXLINE], recvline[MAXLINE];

    while( fgets(sendline, MAXLINE, stdin) != NULL)
    {
        sockfd->Writen(sendline, strlen(sendline));

        if(sockfd->Read(recvline, MAXLINE) == 0)
        {
            std::cout << "str_cli: server terminated prematurely";
        }

        fputs(recvline, stdout);
        memset(recvline, 0, MAXLINE);
    }
}

int main(int argc, char **argv)
{
    Socket *sockfd;
    SockAddr *servaddr;

    if(argc != 2)
    {
        std::cout << "uasge: tcpcli <IPaddress>" << std::endl;
        return -1;
    }

    sockfd = new Socket(AF_INET, SOCK_STREAM, 0);
    servaddr = new SockAddr(AF_INET, argv[1], 9877);

    sockfd->Connect(servaddr);

    str_cli(sockfd);

    return 0;
}
