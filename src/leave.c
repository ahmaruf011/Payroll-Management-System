#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/leave.h"
#include "../include/employee.h"
#include "../include/activity.h"
#include "../include/utils.h"
Leave *frontLeave = NULL;
Leave *rearLeave = NULL;

void leaveManagement()
{
    int choice;

    while(1)
    {
        clearScreen();
        
        printf("\n========== LEAVE MANAGEMENT ==========\n");

        printf("1. View Pending Leave\n");
        printf("2. Approve Leave\n");
        printf("3. Reject Leave\n");
        printf("4. Leave History\n");
        printf("5. Back\n");

        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                viewPendingLeave();
                break;

            case 2:
                approveLeave();
                break;

            case 3:
                rejectLeave();
                break;

            case 4:
                leaveHistory();
                break;

            case 5:
                return;

            default:
                printf("\nInvalid Choice.\n");
        }
        printf("\nPress Enter to Continue...");
getchar();
getchar();
    }
}
void saveLeave()
{
    FILE *fp = fopen("data/leave.txt", "w");

    if(fp == NULL)
        return;

    Leave *temp = frontLeave;

    while(temp != NULL)
    {
        fprintf(fp, "%d|%s|%s|%s|%s\n",
                temp->employeeID,
                temp->fromDate,
                temp->toDate,
                temp->reason,
                temp->status);

        temp = temp->next;
    }

    fclose(fp);
}
void applyLeave(int employeeID)
{
    Leave *newNode = (Leave *)malloc(sizeof(Leave));

    newNode->employeeID = employeeID;

    printf("From Date (DD/MM/YYYY) : ");
    scanf("%19s", newNode->fromDate);
    if(!isValidDate(newNode->fromDate))
{
    printf("\nInvalid From Date.\n");
    free(newNode);
    return;
}

    printf("To Date (DD/MM/YYYY) : ");
    scanf("%19s", newNode->toDate);
    if(!isValidDate(newNode->toDate))
{
    printf("\nInvalid To Date.\n");
    free(newNode);
    return;
}
int newFrom = dateToNumber(newNode->fromDate);
int newTo = dateToNumber(newNode->toDate);
if(newFrom > newTo)
{
    printf("\nFrom Date Cannot Be Greater Than To Date.\n");
    free(newNode);
    return;
}
Leave *temp = frontLeave;

while(temp != NULL)
{
    if(temp->employeeID == employeeID)
    {
        int oldFrom = dateToNumber(temp->fromDate);
        int oldTo = dateToNumber(temp->toDate);

        if(newFrom <= oldTo && newTo >= oldFrom)
        {
            printf("\nLeave Already Exists For These Dates.\n");
            free(newNode);
            return;
        }
    }

    temp = temp->next;
}
    printf("Reason : ");
    scanf(" %99[^\n]", newNode->reason);
    if(strlen(newNode->reason) == 0)
{
    printf("\nReason Cannot Be Empty.\n");
    free(newNode);
    return;
}

    strcpy(newNode->status, "Pending");

    newNode->next = NULL;

    if(frontLeave == NULL)
    {
        frontLeave = rearLeave = newNode;
    }
    else
    {
        rearLeave->next = newNode;
        rearLeave = newNode;
    }
    saveLeave();

    printf("\nLeave Applied Successfully.\n");
    logActivity("Leave Applied");
}

void viewPendingLeave()
{
    Leave *temp = frontLeave;
    int found = 0;

    if(frontLeave == NULL)
    {
        printf("\nNo Leave Records Found.\n");
        return;
    }

    while(temp != NULL)
    {
        if(strcmp(temp->status, "Pending") == 0)
        {
            printf("\nEmployee ID : %d\n", temp->employeeID);
            printf("From Date   : %s\n", temp->fromDate);
            printf("To Date     : %s\n", temp->toDate);
            printf("Reason      : %s\n", temp->reason);
            printf("Status      : %s\n", temp->status);

            found = 1;
        }

        temp = temp->next;
    }

    if(!found)
    {
        printf("\nNo Pending Leave Found.\n");
    }
}

void approveLeave()
{
    int id;

    Leave *temp = frontLeave;

    if(frontLeave == NULL)
    {
        printf("\nNo Leave Found.\n");
        return;
    }

    printf("\nEnter Employee ID : ");
    scanf("%d",&id);

    while(temp != NULL)
    {
        if(temp->employeeID == id && strcmp(temp->status,"Pending")==0)
        {
            strcpy(temp->status,"Approved");

            saveLeave();

            printf("\nLeave Approved Successfully.\n");
            logActivity("Leave Approved");
            return;
        }

        temp = temp->next;
    }

    printf("\nPending Leave Not Found.\n");
}
void rejectLeave()
{
    int id;

    Leave *temp = frontLeave;

    if(frontLeave == NULL)
    {
        printf("\nNo Leave Found.\n");
        return;
    }

    printf("\nEnter Employee ID : ");
    scanf("%d",&id);

    while(temp != NULL)
    {
        if(temp->employeeID == id && strcmp(temp->status,"Pending")==0)
        {
            strcpy(temp->status,"Rejected");

            saveLeave();

            printf("\nLeave Rejected Successfully.\n");
            logActivity("Leave Rejected");
            return;
        }

        temp = temp->next;
    }

    printf("\nPending Leave Not Found.\n");
}

void myLeaveHistory(int employeeID)
{
    Leave *temp = frontLeave;
    int found = 0;

    if(frontLeave == NULL)
    {
        printf("\nNo Leave History Found.\n");
        return;
    }

    while(temp != NULL)
    {
        if(temp->employeeID == employeeID)
        {
            printf("\n=====================================\n");
            printf("Employee ID : %d\n", temp->employeeID);
            printf("From Date   : %s\n", temp->fromDate);
            printf("To Date     : %s\n", temp->toDate);
            printf("Reason      : %s\n", temp->reason);
            printf("Status      : %s\n", temp->status);

            found = 1;
        }

        temp = temp->next;
    }

    if(found == 0)
    {
        printf("\nNo Leave History Found.\n");
    }
}
void loadLeave()
{
    FILE *fp = fopen("data/leave.txt", "r");

    if(fp == NULL)
        return;

    while(1)
    {
        Leave *newNode = (Leave *)malloc(sizeof(Leave));

        if(fscanf(fp,"%d|%19[^|]|%19[^|]|%99[^|]|%19[^\n]\n",
                  &newNode->employeeID,
                  newNode->fromDate,
                  newNode->toDate,
                  newNode->reason,
                  newNode->status) != 5)
        {
            free(newNode);
            break;
        }

        newNode->next = NULL;

        if(frontLeave == NULL)
        {
            frontLeave = rearLeave = newNode;
        }
        else
        {
            rearLeave->next = newNode;
            rearLeave = newNode;
        }
    }

    fclose(fp);
}
void deleteLeaveRecord(int employeeID)
{
    Leave *temp = frontLeave;
    Leave *prev = NULL;

    while(temp != NULL)
    {
        if(temp->employeeID == employeeID)
        {
            Leave *deleteNode = temp;

            if(prev == NULL)
            {
                frontLeave = temp->next;
                temp = frontLeave;

                if(frontLeave == NULL)
                    rearLeave = NULL;
            }
            else
            {
                prev->next = temp->next;

                if(temp == rearLeave)
                    rearLeave = prev;

                temp = prev->next;
            }

            free(deleteNode);
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }

    saveLeave();
}
void leaveHistory()
{
    Leave *temp = frontLeave;

    if(frontLeave == NULL)
    {
        printf("\nNo Leave History Found.\n");
        return;
    }

    while(temp != NULL)
    {
        printf("\n=====================================\n");
        printf("Employee ID : %d\n", temp->employeeID);
        printf("From Date   : %s\n", temp->fromDate);
        printf("To Date     : %s\n", temp->toDate);
        printf("Reason      : %s\n", temp->reason);
        printf("Status      : %s\n", temp->status);

        temp = temp->next;
    }
}