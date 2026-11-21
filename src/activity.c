#include <stdio.h>
#include <time.h>

#include "../include/activity.h"

void logActivity(const char action[])
{
    FILE *fp = fopen("data/activity.txt","a");

    if(fp == NULL)
        return;

    time_t now = time(NULL);

    fprintf(fp,"%s : %s",action,ctime(&now));

    fclose(fp);
}