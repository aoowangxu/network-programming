/*************************************************************************
	> File Name: udp_client.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 03 Apr 2016 08:31:31 AM EDT
 ************************************************************************/

#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#define BUFSIZE 1000

int main()
{
    int s;
    int len;
    socklen_t sin_size;
    char buf[BUFSIZE];

    struct sockaddr_in remote_addr;
    struct sockaddr_in my_addr;
    memset(&remote_addr, 0, sizeof(remote_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    my_addr.sin_port = htons(8000);

    if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        
        perror("socket");
        return 1;
    }

    sin_size = sizeof(struct sockaddr_in);
    printf("waiting for a packet....\n");
    if(bind(s, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) < 0)
    {
        perror("bind error");
        return 1;
    }
    if((len = recvfrom(s, buf, BUFSIZE, 0, (struct sockaddr *) &remote_addr,&sin_size)) < 0)
    {
        perror("recvfrom");
        return 1;
    }

    printf("recevied packet from %s:\n", inet_ntoa(remote_addr.sin_addr));
    buf[len] = '\0';
    printf("connects : %s\n", buf);
    close(s);
    return 0;
}
