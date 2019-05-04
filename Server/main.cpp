#include <iostream>

#include "../lib/socket.h"
#include "../lib/sockaddr.h"


pid_t Fork()
{
    pid_t pid;

    if((pid = fork()) == -1)
        throw "fork error";

    return pid;
}

void str_echo(Socket *sockfd)
{
    ssize_t n;
    int MAXLINE = 1024;
    char buf[MAXLINE];

    while(true)
    {
        if( (n = sockfd->Read(buf, MAXLINE)) == 0)
            return;

        sockfd->Writen(buf, n);
    }
}

int main(int argc, char **argv)
{
    Socket *listenfd, *connfd;
    SockAddr *cliaddr, *servaddr;
    pid_t childpid;

    listenfd = new Socket(AF_INET, SOCK_STREAM, 0);
    servaddr = new SockAddr(AF_INET, INADDR_ANY, 9877);

    listenfd->Bind(servaddr);
    listenfd->Listen(5);

    while(true)
    {
        connfd = listenfd->Accept(cliaddr);

        if( (childpid = Fork()) == 0)
        {
            listenfd->Close();
            str_echo(connfd);
            exit(0);
        }
        connfd->Close();
    }


    return 0;
}
