#include <stdio.h>
#include <stdlib.h>

#include "../include/login.h"
#include "../include/employee.h"
#include "../include/attendance.h"
#include "../include/leave.h"
#include "../include/salary.h"
#include "../include/loan.h"
#include "../include/activity.h"
#include "../include/utils.h"
void welcomeScreen();
int mainMenu();

int main()
{
    loadAdmin();
    loadEmployees();
    loadAttendance();
    loadLeave();
    loadSalary();
    loadLoan();
    int choice;

    while (1)
    {
           clearScreen();
        welcomeScreen();

        choice = mainMenu();

        switch(choice)
        {
            case 1:
                adminLogin();
                break;

            case 2:
    employeeLogin();
    break;

            case 3:
    printf("\nThank You.\n");
    logActivity("Program Closed");
    exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }

        printf("\nPress Enter to Continue...");
getchar();
getchar();
    }

    return 0;
}

void welcomeScreen()
{
    printf("\n==============================================\n");
    printf("         PAYROLL MANAGEMENT SYSTEM\n");
    printf("==============================================\n");
}

int mainMenu()
{
    int choice;

    printf("\n1. Admin Login\n");
    printf("2. Employee Login\n");
    printf("3. Exit\n");

    printf("\nEnter Choice : ");
    scanf("%d",&choice);

    return choice;
}