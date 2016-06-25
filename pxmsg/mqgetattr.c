/*************************************************************************
	> File Name: mqgetattr.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Apr 2016 05:15:11 AM EDT
 ************************************************************************/

#include<stdio.h>
#include"unpipc.h"

int main(int argc, int **argv)
{
    mqd_t mqd;
    struct mq_attr attr;

    if (argc != 2)
    {
        err_quit("usage; mqgetattr <name>");
    }

    mqd = Mq_open(argv[1], O_RDONLY);

    Mq_getattr(mqd, &attr);
    printf("max #msgs = %ld, max #byte/msg = %ld, *currently on queue  = %ld\n", attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
    Mq_close(mqd);
    exit(0);
}
