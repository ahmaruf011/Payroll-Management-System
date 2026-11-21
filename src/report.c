#include <stdio.h>
#include <string.h>

#include "../include/report.h"
#include "../include/employee.h"
#include "../include/attendance.h"
#include "../include/leave.h"
#include "../include/salary.h"
#include "../include/utils.h"

void reportManagement()
{
    int choice;

    while(1)
    {
         clearScreen();
        printf("\n========== REPORT MANAGEMENT ==========\n");

        printf("1. Total Employees\n");
printf("2. Attendance Report\n");
printf("3. Leave Report\n");
printf("4. Salary Report\n");
printf("5. Department Report\n");
printf("6. Highest Salary\n");
printf("7. Lowest Salary\n");
printf("8. Attendance Percentage\n");
printf("9. Back\n");
        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                totalEmployeesReport();
                break;

            case 2:
                attendanceReport();
                break;

            case 3:
                leaveReport();
                break;

            case 4:
                salaryReport();
                break;

            case 5:
                departmentReport();
                break;

            case 6:
                highestSalaryReport();
                break;

            case 7:
                lowestSalaryReport();
                break;

            case 8:
    attendancePercentageReport();
    break;

case 9:
    return;

            default:
                printf("\nInvalid Choice.\n");
        }
        printf("\nPress Enter to Continue...");
getchar();
getchar();
    }
}
void totalEmployeesReport()
{
    int total = 0;

    Employee *temp = head;

    while(temp != NULL)
    {
        total++;
        temp = temp->next;
    }

    printf("\nTotal Employees : %d\n", total);
}
void attendanceReport()
{
    int present = 0;
    int absent = 0;

    Attendance *temp = front;

    while(temp != NULL)
    {
        if(strcmp(temp->status,"Present")==0)
            present++;
        else
            absent++;

        temp = temp->next;
    }

    printf("\nPresent : %d\n",present);
    printf("Absent  : %d\n",absent);
}

void leaveReport()
{
    int pending = 0;
    int approved = 0;
    int rejected = 0;

    Leave *temp = frontLeave;

    while(temp != NULL)
    {
        if(strcmp(temp->status,"Pending")==0)
            pending++;

        else if(strcmp(temp->status,"Approved")==0)
            approved++;

        else if(strcmp(temp->status,"Rejected")==0)
            rejected++;

        temp = temp->next;
    }

    printf("\nPending  : %d\n",pending);
    printf("Approved : %d\n",approved);
    printf("Rejected : %d\n",rejected);
}
void salaryReport()
{
    Salary *temp = top;

    float total = 0;

    while(temp != NULL)
    {
        total += temp->netSalary;
        temp = temp->next;
    }

    printf("\nTotal Salary Paid : %.2f\n", total);
}
void departmentReport()
{
    char dept[50];
    int found = 0;

    Employee *temp = head;

    printf("\nDepartment : ");
    scanf("%49s", dept);

    while(temp != NULL)
    {
        if(strcmp(temp->department, dept) == 0)
        {
            printf("\n==============================\n");
            printf("Employee ID : %d\n", temp->id);
            printf("Name        : %s\n", temp->name);
            printf("Department  : %s\n", temp->department);
            printf("Designation : %s\n", temp->designation);

            found = 1;
        }

        temp = temp->next;
    }

    if(!found)
    {
        printf("\nNo Employee Found In This Department.\n");
    }
}
void highestSalaryReport()
{
    if(top==NULL)
    {
        printf("\nNo Salary Record.\n");
        return;
    }

    Salary *max=top;
    Salary *temp=top;

    while(temp)
    {
        if(temp->netSalary>max->netSalary)
            max=temp;

        temp=temp->next;
    }

    printf("\nTop Paid Employee\n");

    printf("Employee ID : %d\n",max->employeeID);
    printf("Salary : %.2f\n",max->netSalary);
}
void lowestSalaryReport()
{
    if(top==NULL)
    {
        printf("\nNo Salary Record.\n");
        return;
    }

    Salary *min=top;
    Salary *temp=top;

    while(temp)
    {
        if(temp->netSalary<min->netSalary)
            min=temp;

        temp=temp->next;
    }

    printf("\nLowest Paid Employee\n");

    printf("Employee ID : %d\n",min->employeeID);
    printf("Salary : %.2f\n",min->netSalary);
}
void attendancePercentageReport()
{
    int id;
    int total = 0;
    int present = 0;

    Attendance *temp = front;

    printf("\nEmployee ID : ");
    scanf("%d",&id);

    while(temp != NULL)
    {
        if(temp->employeeID == id)
        {
            total++;

            if(strcmp(temp->status,"Present")==0)
                present++;
        }

        temp = temp->next;
    }

    if(total == 0)
    {
        printf("\nNo Attendance Record Found.\n");
        return;
    }

    printf("\nAttendance Percentage : %.2f%%\n",
           (present * 100.0) / total);
}