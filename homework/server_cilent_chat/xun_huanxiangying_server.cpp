/*************************************************************************
	> File Name: test1.c
	> Author: 
	> Mail: 
	> Created Time: Sun 03 Apr 2016 02:13:51 AM EDT
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<sys/wait.h>
static bool stop = false;

static void handle_term(int sig)
{
    stop = true;
    printf("huidiao hanshu ok?\n\n");
}

int main(int argc, char* argv[])
{
    signal(SIGTERM, handle_term);
    if(argc <= 3)
    {
        printf("usage: %s ip_address port_number backlog\n", basename(argv[0]));
        return 11;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int ret = bind(sock, (struct sockaddr*) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, backlog);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
    pid_t id = fork();
    if(connfd < 0)
    {
        printf("erroris :%d\n", -1);
    }
    else
    {
        while(1)
        {
            if (id < 0)
            {
                return 1;
            }
            else if (0 == id)
            {
                char recvbuf[1024] = {'\0'};
                int len = recv(connfd, recvbuf, sizeof(recvbuf), 0);
                if(len > 0)
                {
                    recvbuf[len] ='\0';
                    printf("client: %s\n", recvbuf);     
                }
                else 
                {
                    break;
                }
            }
            else
            {
                char sendbuff[1024] = {'\0'};
                gets(sendbuff);
                if (strcmp(sendbuff, "quit") == 0)
                {
                    break;
                }
                send(connfd, sendbuff, strlen(sendbuff), 0);
                char remote[INET_ADDRSTRLEN];
            }

            
        }
    }
    waitpid(id, NULL, 0);
    close(connfd);
    close(sock);
    return 0;
    
}
