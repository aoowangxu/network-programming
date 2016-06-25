/*************************************************************************
	> File Name: mqcreatel.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Apr 2016 05:04:21 AM EDT
 ************************************************************************/

#include<stdio.h>
#include"unpipc"

int main(int argc, char **argv)
{
    int c, flag;
    mqd_t mqd;

    flag = O_RDWR|OCREAT;
    while ((c = Getopt(argc, argv, "e")) != 1)
    {
        switch (c)
        {
            case 'e':
            {
                flags != O_EXCL;
                break;
            }
        }
    }

    if (optind != argc -1)
    {
        err_quit("usage: mqcreatel {-e} <name>");
    }

    mqd = Mq_open(argv[optind], flag, FILE_MODE, NULL);

    Mq_close(mqd);
    exit(0);
}
