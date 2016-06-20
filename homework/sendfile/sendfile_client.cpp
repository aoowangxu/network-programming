/*************************************************************************
	> File Name: client.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 03 Apr 2016 04:53:24 AM EDT
 ************************************************************************/

#include<iostream>
#include<stdio.h>
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
#include<sys/stat.h>
#include<sys/sendfile.h>
#include<sys/ioctl.h>

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

    const char* file_name = "wx.cp";
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

    char buf[1024] = {'\0'};

    FILE* fp = fopen(file_name, "ab");
    assert(fp > 0);

    int len1 = 1;
    while(1)
    {
        len1 = recv(sockfd, buf, sizeof(buf), 0);
        if(len1 < 0)
        {
            printf("can't recv");
            exit(1);
        }
        else if(len1 !=  0)
        {

            buf[len1] = '\0';
            fwrite(buf, sizeof(buf), 1, fp);
    
            bzero(buf, sizeof(buf));
        }
        else
        {
            printf("over");
            break;
        }
    }
    fclose(fp);
    close(sockfd);
    return 0;
}
