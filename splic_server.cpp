/*************************************************************************
	> File Name: splic_server.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 10 Apr 2016 08:58:15 AM EDT
 ************************************************************************/

#include"net.h"

int main(int argc, char* argv[])
{
    if(argc <= 2)
    {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr*) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength );
    if(connfd < 0)
    {
        printf("error is : %d", errno);
    }
    else
    {
        int pipefd[2];
        assert(ret != -1);
        ret = pipe(pipefd);

        ret = splice(connfd, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE|SPLICE_F_MOVE);
        assert(ret != -1);
        close(connfd);
    }

    close(connfd);
    return 0;
}
