/*************************************************************************
	> File Name: client.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 03 Apr 2016 04:53:24 AM EDT
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("usage %s <sever ip> <server port>\n", argv[0]);
        return -1;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("socket creaat failed.");
        exit(-1);
    }

    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sockfd, (struct sockaddr*)&addr, addrlen) < 0)
    {
        perror("socket connect failed");
        exit(-1);
    }
    printf("connect to %s\n", argv[1]);

    while(1)
    {
        char sendbuff[1024] = "cilent:: elcome to learn the socket coding..";
        printf("input string: ");
        //scanf("%s", sendbuff);
        gets(sendbuff);
        if(strcmp(sendbuff, "quit") == 0)
        {
            break;
        }
        send(sockfd, sendbuff, strlen(sendbuff), 0);
        printf("....send some msg to server.....\n");
        char buf[1024] = {0};
        int len = recv(sockfd, buf, sizeof(buf), 0);
        if(len >= 0)
        {
            buf[len] = '\0';
        }
        printf("client_recv: %s\n", buf);
        
    }
    close(sockfd);
    return 0;
}
