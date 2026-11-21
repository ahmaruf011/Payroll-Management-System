#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/notice.h"
#include "../include/activity.h"
#include "../include/utils.h"

void addNotice()
{
    FILE *fp = fopen("data/notice.txt","a");

    if(fp == NULL)
    {
        printf("\nFile Error!\n");
        return;
    }

    char notice[500];

    getchar();

    printf("\nEnter Notice:\n");
    scanf("%499[^\n]", notice);

    if(strlen(notice) == 0)
    {
        printf("\nNotice Cannot Be Empty.\n");
        fclose(fp);
        return;
    }

    fprintf(fp,
            "\n=====================================\n");
    fprintf(fp,"%s\n",notice);
    fprintf(fp,
            "=====================================\n");

    fclose(fp);

    logActivity("Notice Updated");

    printf("\nNotice Saved Successfully.\n");
}
void viewNotice()
{
    FILE *fp = fopen("data/notice.txt","r");

    if(fp == NULL)
    {
        printf("\nNo Notice Available.\n");
        return;
    }

    char line[500];
    char latest[5000] = "";

    while(fgets(line, sizeof(line), fp))
    {
        if(strcmp(line, "=====================================\n") == 0)
        {
            latest[0] = '\0';

            strcat(latest, line);

            while(fgets(line, sizeof(line), fp))
            {
                strcat(latest, line);

                if(strcmp(line, "=====================================\n") == 0)
                    break;
            }
        }
    }

    fclose(fp);

    if(strlen(latest) == 0)
    {
        printf("\nNo Notice Available.\n");
        return;
    }

    printf("\n========== CURRENT NOTICE ==========\n\n");
    printf("%s", latest);
}
void noticeManagement()
{
    int choice;

    while(1)
    {
         clearScreen();
        printf("\n========== NOTICE BOARD ==========\n");

        printf("1. Add / Update Notice\n");
        printf("2. View Notice\n");
        printf("3. Notice History\n");
        printf("4. Back\n");
        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addNotice();
                break;

            case 2:
                viewNotice();
                break;

            case 3:
    noticeHistory();
    break;

case 4:
    return;
            default:
                printf("\nInvalid Choice.\n");
        }
        printf("\nPress Enter to Continue...");
getchar();
getchar();
    }
}
void noticeHistory()
{
    FILE *fp = fopen("data/notice.txt","r");

    if(fp==NULL)
    {
        printf("\nNo Notice Found.\n");
        return;
    }

    char line[500];

    printf("\n========== NOTICE HISTORY ==========\n");

    while(fgets(line,sizeof(line),fp))
    {
        printf("%s",line);
    }

    fclose(fp);
}