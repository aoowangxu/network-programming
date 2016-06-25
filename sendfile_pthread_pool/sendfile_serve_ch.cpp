/*************************************************************************
	> File Name: sendfile_serve.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Apr 2016 05:13:40 AM EDT
 ************************************************************************/

#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/sendfile.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<pthread.h>

typedef struct 
{
    pthread_t thread_tid;
    long thread_count;
}Thread;
    Thread* tptr;
    int listenfd, nthreads;
    socklen_t addrlen;
    pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;

    int filefd;
    struct stat stat_buf;


void thread_make(int i)
{
    void *thread_main(void *);
    pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void *)i);
    return;
}

void thread_main(void *arg)
{
    int connfd;
    void child(int);
    socklen_t clilen;
    struct sockaddr* cliaddr;

    cliaddr = (struct sockaddr *)malloc(sizeof(addrlen));
    printf("%ld", (long )cliaddr);
    printf("thread %d starting \n", (int) arg);
    while (1)
    {
        clilen = addrlen;
        pthread_mutex_lock(&mlock);
        connfd = accept(listenfd, cliaddr, &clilen);//error 88 socket operation on non_socket;
        if(connfd < 0)
        {
           printf("errno is : %d\n", errno);
        }
        pthread_mutex_unlock(&mlock);
        tptr[(int)arg].thread_count++;

        child(connfd);
        close(connfd);
    }
}

int main(int argc, char *argv[])
{
    if(argc <= 4)
    {
        printf("usage: %s ip_address port_number file_name  nthreads", basename(argv[0]));
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);
    const char* file_name = argv[3];
    nthreads = atoi(argv[4]);
    tptr = (Thread *)calloc(nthreads, sizeof(nthreads));

    int filefd = open(file_name, O_RDONLY);
    printf("%d****", filefd);
    assert(filefd > 0);
    fstat(filefd, &stat_buf);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);
    listenfd = sock;

    for (int i = 0; i < nthreads; ++i)
    {
        thread_make(i);
    }

    //signal(SIGINT, sig_int);

    while (1)
    {
        pause();
    }
    close(filefd);
    close(sock);
    return 0;
}

void child(int sockfd)
{
    printf("%d, %d, %d\n", (int)stat_buf.st_size, filefd, sockfd);
    unsigned int n = sendfile(sockfd, 3, NULL, stat_buf.st_size);
    if (n > 0)
    {
        printf("sendfile succes ***%d****\n", n );
    }
    else
    {
        printf("sendfile failed ***%d****\n", n );
    }
    return;
}
