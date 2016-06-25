/*************************************************************************
	> File Name: mqunlink.c
	> Author: 
	> Mail: 
	> Created Time: Sun 24 Apr 2016 05:11:41 AM EDT
 ************************************************************************/

#include<stdio.h>
#include"unpipc.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        err_quit("usage: mqunlink <name>");
    }

    Mq_unlink(argv[1]);
    exit(0);

}
