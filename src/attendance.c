#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/attendance.h"
#include "../include/employee.h"
#include "../include/activity.h"
#include "../include/leave.h"
#include "../include/utils.h"

Attendance *front = NULL;
Attendance *rear = NULL;
void saveAttendance()
{
    FILE *fp = fopen("data/attendance.txt", "w");

    if(fp == NULL)
        return;

    Attendance *temp = front;

    while(temp != NULL)
    {
        fprintf(fp, "%d|%s|%s\n",
                temp->employeeID,
                temp->date,
                temp->status);

        temp = temp->next;
    }

    fclose(fp);
}
void attendanceManagement()
{
    int choice;

    while(1)
    {
         clearScreen();
        
        printf("\n========== ATTENDANCE MANAGEMENT ==========\n");

        printf("1. Mark Attendance\n");
        printf("2. View Attendance\n");
        printf("3. Search Attendance\n");
        printf("4. Update Attendance\n");
        printf("5. Delete Attendance\n");
        printf("6. Back\n");

        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                markAttendance();
                break;

            case 2:
                viewAttendance();
                break;

            case 3:
                searchAttendance();
                break;

            case 4:
                updateAttendance();
                break;

            case 5:
                deleteAttendance();
                break;

            case 6:
                return;

            default:
                printf("\nInvalid Choice.\n");
        }
        printf("\nPress Enter to Continue...");
getchar();
getchar();
    }
}

void markAttendance()
{
    Attendance *newNode = (Attendance*)malloc(sizeof(Attendance));

    printf("\nEmployee ID : ");
    scanf("%d",&newNode->employeeID);

    if(!employeeExists(newNode->employeeID))
    {
        printf("\nEmployee ID Not Found.\n");
        free(newNode);
        return;
    }

    printf("Date (DD/MM/YYYY) : ");
    scanf("%19s", newNode->date);
    if(!isValidDate(newNode->date))
{
    printf("\nInvalid Date.\n");
    free(newNode);
    return;
}

    Attendance *temp = front;

    while(temp != NULL)
    {
        if(temp->employeeID == newNode->employeeID &&
           strcmp(temp->date, newNode->date) == 0)
        {
            printf("\nAttendance Already Marked For This Date.\n");
            free(newNode);
            return;
        }

        temp = temp->next;
    }

    int autoLeave = 0;

    Leave *leaveTemp = frontLeave;

    while(leaveTemp != NULL)
    {
        if(leaveTemp->employeeID == newNode->employeeID &&
           strcmp(leaveTemp->status, "Approved") == 0)
        {
            int attendanceDate = dateToNumber(newNode->date);
            int fromDate = dateToNumber(leaveTemp->fromDate);
            int toDate = dateToNumber(leaveTemp->toDate);

            if(attendanceDate >= fromDate &&
               attendanceDate <= toDate)
            {
                strcpy(newNode->status, "Leave");
                autoLeave = 1;
                break;
            }
        }

        leaveTemp = leaveTemp->next;
    }

    if(autoLeave)
    {
        printf("\nApproved Leave Found.\n");
        printf("Attendance Automatically Marked As Leave.\n");
    }
    else
    {
        while(1)
        {
            printf("Status (P = Present | A = Absent) : ");
            scanf("%19s", newNode->status);

            if(strcmp(newNode->status,"P")==0 || strcmp(newNode->status,"p")==0)
            {
                strcpy(newNode->status,"Present");
                break;
            }

            if(strcmp(newNode->status,"A")==0 || strcmp(newNode->status,"a")==0)
            {
                strcpy(newNode->status,"Absent");
                break;
            }

            printf("\nInvalid Status! Enter P or A Only.\n");
        }
    }

    newNode->next = NULL;

    if(front == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    saveAttendance();

    printf("\nAttendance Marked Successfully.\n");
    logActivity("Attendance Marked");
}

void viewAttendance()
{
    Attendance *temp = front;

    if(temp == NULL)
    {
        printf("\nNo Attendance Found.\n");
        return;
    }

    while(temp != NULL)
    {
        printf("\nEmployee ID : %d\n",temp->employeeID);
        printf("Date : %s\n",temp->date);
        printf("Status : %s\n",temp->status);

        temp = temp->next;
    }
}

void searchAttendance()
{
    int id;

    Attendance *temp = front;

    printf("\nEmployee ID : ");
    scanf("%d",&id);

    while(temp != NULL)
    {
        if(temp->employeeID == id)
        {
            while(temp != NULL && temp->employeeID == id)
            {
                printf("\nEmployee ID : %d\n", temp->employeeID);
                printf("Date : %s\n", temp->date);
                printf("Status : %s\n", temp->status);

                temp = temp->next;
            }

            return;
        }

        temp = temp->next;
    }

    printf("\nAttendance Not Found.\n");
}

void updateAttendance()
{
    int id;
    Attendance *temp = front;

    if(front == NULL)
    {
        printf("\nNo Attendance Found.\n");
        return;
    }

    printf("\nEnter Employee ID : ");
    scanf("%d", &id);

    while(temp != NULL)
    {
        if(temp->employeeID == id)
        {
            printf("New Date (DD/MM/YYYY) : ");
            scanf("%19s", temp->date);

            if(!isValidDate(temp->date))
            {
                printf("\nInvalid Date.\n");
                return;
            }

            while(1)
            {
                printf("New Status (Present/Absent/Leave) : ");
                scanf("%19s", temp->status);

                if(strcmp(temp->status, "Present") == 0 ||
                   strcmp(temp->status, "Absent") == 0 ||
                   strcmp(temp->status, "Leave") == 0)
                {
                    break;
                }

                printf("\nInvalid Status! Enter Present, Absent or Leave.\n");
            }

            saveAttendance();

            printf("\nAttendance Updated Successfully.\n");

            logActivity("Attendance Updated");

            return;
        }

        temp = temp->next;
    }

    printf("\nAttendance Not Found.\n");
}
void deleteAttendance()
{
    int id;
    char date[20];

    Attendance *temp = front;
    Attendance *prev = NULL;

    if(front == NULL)
    {
        printf("\nNo Attendance Found.\n");
        return;
    }

    printf("\nEmployee ID : ");
    scanf("%d",&id);

    printf("Date (DD/MM/YYYY) : ");
    scanf("%19s",date);

    while(temp != NULL)
    {
        if(temp->employeeID == id &&
           strcmp(temp->date, date) == 0)
        {
            if(prev == NULL)
            {
                front = temp->next;

                if(front == NULL)
                    rear = NULL;
            }
            else
            {
                prev->next = temp->next;

                if(temp == rear)
                    rear = prev;
            }

            free(temp);

            saveAttendance();

            printf("\nAttendance Deleted Successfully.\n");

            logActivity("Attendance Deleted");

            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\nAttendance Record Not Found.\n");
}
void loadAttendance()
{
    FILE *fp=fopen("data/attendance.txt","r");

    if(fp==NULL)
        return;

    while(1)
    {
        Attendance *newNode=(Attendance*)malloc(sizeof(Attendance));

        if(fscanf(fp,"%d|%19[^|]|%19[^\n]\n",
                  &newNode->employeeID,
                  newNode->date,
                  newNode->status)!=3)
        {
            free(newNode);
            break;
        }

        newNode->next=NULL;

        if(front==NULL)
        {
            front=rear=newNode;
        }
        else
        {
            rear->next=newNode;
            rear=newNode;
        }
    }

    fclose(fp);
}
void deleteAttendanceRecord(int employeeID)
{
    Attendance *temp = front;
    Attendance *prev = NULL;

    while(temp != NULL)
    {
        if(temp->employeeID == employeeID)
        {
            Attendance *deleteNode = temp;

            if(prev == NULL)
            {
                front = temp->next;
                temp = front;

                if(front == NULL)
                    rear = NULL;
            }
            else
            {
                prev->next = temp->next;

                if(temp == rear)
                    rear = prev;

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

    saveAttendance();
}