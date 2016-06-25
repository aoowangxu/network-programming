/*************************************************************************
	> File Name: prodcons3.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Apr 2016 04:23:34 AM EDT
 ************************************************************************/

#include<stdio.h>

int main(int argc, char **argv)
{
    int i, nthreads, count[MAXNTHREADS];
    pthread_t tid_produce[MAXNTHREADS], tid_consume;
    
    if (argc != 3)
    {
        err_quit("usage: prodcons3 <#items> <#threads>");
    }
    nitems = min((atoi(argv[1]), MAXNITEMS));
    nthreads = min(atoi(argv[2]), MAXNTHREADS);

    Set_concurrency(nthreads + 1);
    for (i = 0; i < nthreads; ++i)
    {
        count[i] = 0;
        Pthread_create(&tid_produce[i], NULL, produce, &count[i]);
    }

    Pthread_create(&tid_consume, NULL, consume, NULL);

    for (i = 0; i  < nthreads; ++i)
    {
        Pthread_join(tid_produce[i], NULL);
        printf("count[%d] = %d\n", i, count[i]);
    }

    Pthread_join(tid_consume, NULL);
    exit(0);
}

void consume_wait(int i)
{
    for ( ; ; )
    {
        Pthread_mutex_lock(&shared.mutex);
        if (i < shared.nput)
        {
            Pthread_mutex_unlock(&shared.mutex);
            return ;
        }
        Pthread_mutex_unlock(&shared.mutex);
    }
}

void *consume(void *arg)
{
    int i;
    for (i = 0; i < nitems; ++i)
    {
        consume_wait(i);
        if (shared.buff[i] != i)
        {
            printf("buff[%d] = %d\n", i, shared.buff[i]);
        }
    }
    return (NULL);
}
