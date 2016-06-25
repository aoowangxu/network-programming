/*************************************************************************
	> File Name: mqcreate.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Apr 2016 05:22:23 AM EDT
 ************************************************************************/

#include<stdio.h>
#include"unpipc.h"

struct mq_attr attr;

int main(int argc, char **argv)
{
    int c, flag;
    mqd_t mqd;
    flag = O_RDWR|O_CREAT;
    while ((c = Getopt(argc, argv, "em:z:")) != -1)
    {
        switch(c)
        {
            case 'e':
            {
                flaf |= O_EXCL;
                break;
            }
            case 'm':
            {
                attr.mq_maxmsg = atoi(optarg);
                break;
            }
            case 'z':
            {
                attr.mqgsize = atoi(optarg);
                break;
            }
        }
    }

    if (optind != argc-1)
    {
        ree_quit("usage : mqcreate {-e} [-m maxmsg -z msgsize] <name>");
    }

    if ((attr.mq_maxmsg != 0 && attr.mqgsize ==0) || (attr.mq_maxmsg == 0 && attr.mqgsize != 0))
    {
        err_quit("must specity both -m maxmsg and -z msgsize");
    }

    mqd = Mq_open(argv[optind], flag, FILE_MODE, (attr.mq_maxmsg != 0) ? &attr: NULL);
    Mq_close(mqd);
    exit(0);
}
