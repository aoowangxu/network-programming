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

    const char* file_name = "copy";
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


    FILE* fp = fopen(file_name, "w");
    assert(fp > 0);
    int fp_n = fileno(fp);
    int pipefd[2];
    int ret = pipe(pipefd);
    assert(ret != -1);

    while(1)
    {
        ret = splice(sockfd, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
        if (ret < 0)
        {
            printf("splice1 () error");
            exit(1);
        }
        if(ret == 0)
        {
            break;
        }
        ret = splice(pipefd[0], NULL, fp_n, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
        if (ret < 0)
        {
            printf("splice2 () error");
            exit(1);
        }
    }
    fclose(fp);
    close(sockfd);
    return 0;
}
