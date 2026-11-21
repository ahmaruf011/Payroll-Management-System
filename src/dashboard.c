#include <stdio.h>
#include <stdlib.h>
#include "../include/dashboard.h"
#include "../include/employee.h"
#include "../include/attendance.h"
#include "../include/leave.h"
#include "../include/report.h"
#include "../include/activity.h"
#include "../include/salary.h"
#include "../include/notice.h"
#include "../include/login.h"
#include "../include/loan.h"
#include "../include/utils.h"
void dashboardSummary()
{
    int employee = 0;
    int attendance = 0;
    int leave = 0;

    float totalSalary = 0;

    Employee *e = head;
    Attendance *a = front;
    Leave *l = frontLeave;
    Salary *s = top;

    while(e)
    {
        employee++;
        e = e->next;
    }

    while(a)
    {
        attendance++;
        a = a->next;
    }

    while(l)
    {
        leave++;
        l = l->next;
    }

    while(s)
    {
        totalSalary += s->netSalary;
        s = s->next;
    }

    printf("\n=====================================\n");
    printf("          DASHBOARD SUMMARY\n");
    printf("=====================================\n");

    printf("Total Employees   : %d\n",employee);
    printf("Attendance Record : %d\n",attendance);
    printf("Leave Records     : %d\n",leave);
    printf("Total Salary Paid : %.2f\n",totalSalary);

    printf("=====================================\n");
}

void adminDashboard()
{
    int choice;

    while (1)
    {
        clearScreen();
        dashboardSummary();

        printf("\n==============================================\n");
        printf("              ADMIN DASHBOARD\n");
        printf("==============================================\n");

        printf("1. Employee Management\n");
        printf("2. Attendance Management\n");
        printf("3. Leave Management\n");
        printf("4. Salary Management\n");
        printf("5. Report Management\n");
        printf("6. Notice Board\n");
        printf("7. Change Admin Password\n");
        printf("8. Loan Management\n");
        printf("9. Logout\n");

        printf("\nEnter Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
    employeeManagement();
    break;
            case 2:
    attendanceManagement();
    break;

            case 3:
    leaveManagement();
    break;

            case 4:
    salaryManagement();
    break;

case 5:
    reportManagement();
    break;
            case 6:
    noticeManagement();
    break;
            case 7:
    changeAdminPassword();
    break;
    case 8:
    loanManagement();
    break;

            case 9:
                return;

            default:
                printf("\nInvalid Choice!\n");
        }

      printf("\nPress Enter to Continue...");
getchar();
getchar();
    }
}
void employeeDashboard(Employee *currentEmployee)
{
    int choice;

    while(1)
    {
        clearScreen();
        printf("\n========== EMPLOYEE DASHBOARD ==========\n");
        printf("1. View Profile\n");
        printf("2. Salary Slip\n");
        printf("3. Apply Leave\n");
        printf("4. Leave History\n");
        printf("5. Apply Loan\n");
        printf("6. Loan History\n");
        printf("7. View Notice\n");
        printf("8. Change Password\n");
        printf("9. Logout\n");

        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("\n========== MY PROFILE ==========\n");
                printf("ID           : %d\n", currentEmployee->id);
                printf("Name         : %s\n", currentEmployee->name);
                printf("Department   : %s\n", currentEmployee->department);
                printf("Designation  : %s\n", currentEmployee->designation);
                printf("Phone        : %s\n", currentEmployee->phone);
                printf("Email        : %s\n", currentEmployee->email);
                printf("Basic Salary : %.2f\n", currentEmployee->basicSalary);
                break;

            case 2:
                mySalarySlip(currentEmployee->id);
                break;

            case 3:
                applyLeave(currentEmployee->id);
                break;

            case 4:
    myLeaveHistory(currentEmployee->id);
    break;
            case 5:
                applyLoan(currentEmployee->id);
                break;

            case 6:
                loanHistory(currentEmployee->id);
                break;

            case 7:
                viewNotice();
                break;

            case 8:
                changeEmployeePassword(currentEmployee);
                break;

            case 9:
                return;

            default:
                printf("\nInvalid Choice!\n");
        }
        printf("\nPress Enter To Continue...");
getchar();
getchar();

    }
}