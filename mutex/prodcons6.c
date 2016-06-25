/*************************************************************************
	> File Name: prodcons6.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Apr 2016 04:40:20 AM EDT
 ************************************************************************/

#include<stdio.h>
#include"unpipc.h"

#define MAXNITEMS 1000000
#define MAXNTHREADS 1000000
int nitems;
int buff[MAXNITEMS];
struct
{
    pthread_mutex_t mutex;
    int nput;
    int nval;
} put = {PTHREAD_MUTEX_INITALIZER};

struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int nready;
}nready = {PTJREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER}；


void *produce(void *arg)
{
    for ( ; ; )
    {
        pthread_mutex_lock(&put.mutex);
        if (put.nput >= nitems)
        {
            pthread_mutex_uncock(&put.mutex);
            return (NULL);
        }
        buff[put.nput] = put.nval;
        put.nval++;
        put.nput++;
        Pthread_mutex_uncock(&put.mutex);

        Pthread_mutex_lock(&nready.cond);
        if (nready.nready == 0)
        {
            Pthread_cond_signal(&nready.cond);
        }
        nready.nready++;
        Pthread_mutex_uncock(&nready.mutex);

        *((int *)arg) += 1;
    }
}

void *consume(void *arg)
{
    int i;
    for (i = 0; i < nitems; ++i)
    {
        Pthread_mutex_lock(&nready.mutex);
        while (nredy.nready == 0)
        {
            Pthread_cond_wait(&nready.cond, &nready.mutex);
        }
        nready.nready--;
        Pthread_mutex_uncock(&nready.mutex);

        if (buff[i] != i)
        {
            printf("buf[%d] = %d\n", i, buff[i]);
        }
    }
    return (NULL);
}

