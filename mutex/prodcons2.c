/*************************************************************************
	> File Name: prodcons2.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Apr 2016 03:40:01 AM EDT
 ************************************************************************/

#include<stdio.h>
//#include"unpipc.h"
#include<sys/types.h>
#include<sys/time.h>
#include<error.h>
#include<fcntl.h>
#include<limits.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAXNITEMS 1000000
#define MAXNTHREADS 100

int nitems;
struct
{
    pthread_mutex_t mutex;
    int buff[MAXNITEMS];
    int nput;
    int nval;
}shared = {PTHREAD_MUTEX_INITIALIZER};

void *produce(void *), *consume(void *);

int main(int argc, char *argv[])
{
    int i, nthreads, count[MAXNTHREADS];
    pthread_t tid_produce[MAXNTHREADS], tid_consume;

    if (argc != 3)
    {
        err_quit("usage: prodcons2 <#items> <#thread>");
    }

    nitems = min(atoi(argv[1]), MAXNITEMS;
    nthreads = min(atoi(argv[2]), MAXNTHREADS);

    Set_concurrency(nthreads);
    for (i = 0; i < nthreads; ++i)
    {
        count[i = 0];
        Pthread_create(&tid_produce[i], NULL, produce, &count[i]);
    }

    for(i = 0; i < nthreads; ++i)
    {
        Pthread_join(tid_produce[i], NULL);
        printf("count[%d] = %d \n", i, count[i]);
    }

    Pthread_creat(&tid_consume, NULL, consume, NULL);
    Pthread_join(tid_consume, NULL);
    return 0;
}


void *produce(void *arg)
    {
        for ( ; ; )
        {
            pthread_mutex_lock(&share.mutex);
            if (shared.nput >= nitems)
            {
                pthread_mutex_unlock(&shared.mutex);
                return (NULL);
            }
            shared.buff[share.nput] = shared.nval;
            shared.nput++;
            shared.nval++;
            pthread_mutex_unlock(&thread.mutex);
            *((int *)arg) += 1;
        }
}

void *consume(void *arg)
{
    int i;
    for (i = 0; i < nitems; ++i)
    {
        if (shared.buff[i] != i)
        {
            printf("buff[%d] = %d\n", shared.buff[i]);
        }
    }
    return (NULL);
}
