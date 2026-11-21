#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/employee.h"
#include "../include/activity.h"
#include "../include/attendance.h"
#include "../include/leave.h"
#include "../include/salary.h"
#include <ctype.h>
#include "../include/utils.h"
#include "../include/loan.h"
Employee *head = NULL;
void saveEmployees()
{
    FILE *fp = fopen("data/employee.txt", "w");

    if(fp == NULL)
        return;

    Employee *temp = head;

    while(temp != NULL)
    {
        fprintf(fp,"%d|%s|%s|%s|%s|%s|%.2f|%s\n",
                temp->id,
                temp->name,
                temp->department,
                temp->designation,
                temp->phone,
                temp->email,
                temp->basicSalary,
                temp->password);

        temp = temp->next;
    }

    fclose(fp);
}

void employeeManagement()
{
    int choice;

    while (1)
    {
        clearScreen();
        
        printf("\n========== EMPLOYEE MANAGEMENT ==========\n");

        printf("1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");
        printf("6. Back\n");

        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                viewEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                updateEmployee();
                break;

            case 5:
                deleteEmployee();
                break;

            case 6:
                return;

            default:
                printf("\nInvalid Choice!\n");
        }
        printf("\nPress Enter to Continue...");
getchar();
getchar();
    }
}

void addEmployee()
{
    Employee *newEmployee;
    int i, valid;

    newEmployee = (Employee*)malloc(sizeof(Employee));

    printf("\nEmployee ID : ");
    scanf("%d",&newEmployee->id);
    if(newEmployee->id <= 0)
{
    printf("\nInvalid Employee ID.\n");
    free(newEmployee);
    return;
}
    if(employeeExists(newEmployee->id))
{
    printf("\nEmployee ID Already Exists.\n");

    free(newEmployee);

    return;
}

    while(1)
{
    printf("Name : ");
    scanf(" %[^\n]", newEmployee->name);

    valid = 1;

    for(i = 0; newEmployee->name[i] != '\0'; i++)
    {
        if(!(isalpha(newEmployee->name[i]) || newEmployee->name[i] == ' '))
        {
            valid = 0;
            break;
        }
    }

    if(valid)
        break;

    printf("Invalid Name! Only letters and spaces are allowed.\n");
}

    printf("Department : ");
    scanf(" %[^\n]",newEmployee->department);

    printf("Designation : ");
    scanf(" %[^\n]",newEmployee->designation);

    while(1)
{
    printf("Phone : ");
    scanf("%s", newEmployee->phone);

    valid = 1;

    if(strlen(newEmployee->phone) != 11)
        valid = 0;

    for(i = 0; newEmployee->phone[i] != '\0'; i++)
    {
        if(!isdigit(newEmployee->phone[i]))
        {
            valid = 0;
            break;
        }
    }

    if(valid)
        break;

    printf("Invalid Phone Number! Enter 11 digits.\n");
}
    while(1)
{
    printf("Email : ");
    scanf("%s", newEmployee->email);

    if(strchr(newEmployee->email, '@') != NULL)
        break;

    printf("Invalid Email! '@' is required.\n");
}
    printf("Basic Salary : ");
    scanf("%f",&newEmployee->basicSalary);
    if(newEmployee->basicSalary <= 0)
{
    printf("\nInvalid Basic Salary.\n");
    free(newEmployee);
    return;
}

    printf("Password : ");
    scanf("%s",newEmployee->password);
    if(strlen(newEmployee->password) < 4)
{
    printf("\nPassword Must Be At Least 4 Characters.\n");
    free(newEmployee);
    return;
}

    newEmployee->next = NULL;

    if(head==NULL)
    {
        head = newEmployee;
    }
    else
    {
        Employee *temp=head;

        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newEmployee;
    }
    saveEmployees();

    printf("\nEmployee Added Successfully.\n");
    logActivity("Employee Added");
}

void viewEmployees()
{
Employee *temp = head;

    if(head == NULL)
    {
        printf("\nNo Employee Found.\n");
        return;
    }

    printf("\n=====================================================================================================================================================\n");
    printf("                                                         EMPLOYEE LIST\n");
    printf("=====================================================================================================================================================\n\n");

    printf("%-8s %-25s %-20s %-25s %-18s %-35s %-12s\n",
           "ID",
           "Name",
           "Department",
           "Designation",
           "Phone",
           "Email",
           "Salary");

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");

    while(temp != NULL)
    {
        printf("%-8d %-25s %-20s %-25s %-18s %-35s %-12.2f\n",
               temp->id,
               temp->name,
               temp->department,
               temp->designation,
               temp->phone,
               temp->email,
               temp->basicSalary);

        temp = temp->next;
    }

    printf("=====================================================================================================================================================\n");
}

void searchEmployee()
{
    int id;

    Employee *temp = head;

    if(head == NULL)
    {
        printf("\nNo Employee Found.\n");
        return;
    }

    printf("\nEnter Employee ID : ");
    scanf("%d",&id);

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            printf("\n========== EMPLOYEE DETAILS ==========\n");

            printf("ID : %d\n",temp->id);
            printf("Name : %s\n",temp->name);
            printf("Department : %s\n",temp->department);
            printf("Designation : %s\n",temp->designation);
            printf("Phone : %s\n",temp->phone);
            printf("Email : %s\n",temp->email);
            printf("Basic Salary : %.2f\n",temp->basicSalary);

            return;
        }

        temp = temp->next;
    }

    printf("\nEmployee Not Found.\n");
}

void updateEmployee()
{
    int id, choice;
    int i, valid;

    Employee *temp = head;

    if(head == NULL)
    {
        printf("\nNo Employee Found.\n");
        return;
    }

    printf("\nEnter Employee ID : ");
    scanf("%d",&id);

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            while(1)
            {
                printf("\n========== UPDATE EMPLOYEE ==========\n");

                printf("1. Name\n");
                printf("2. Department\n");
                printf("3. Designation\n");
                printf("4. Phone\n");
                printf("5. Email\n");
                printf("6. Basic Salary\n");
                printf("7. Password\n");
                printf("8. Back\n");

                printf("\nEnter Choice : ");
                scanf("%d",&choice);

                switch(choice)
                {
                    case 1:

                        while(1)
                        {
                            printf("New Name : ");
                            scanf(" %[^\n]", temp->name);

                            valid = 1;

                            for(i = 0; temp->name[i] != '\0'; i++)
                            {
                                if(!(isalpha(temp->name[i]) || temp->name[i] == ' '))
                                {
                                    valid = 0;
                                    break;
                                }
                            }

                            if(valid)
                                break;

                            printf("Invalid Name! Only letters and spaces are allowed.\n");
                        }

                        saveEmployees();
                        break;

                    case 2:

                        printf("New Department : ");
                        scanf(" %[^\n]", temp->department);

                        saveEmployees();
                        break;

                    case 3:

                        printf("New Designation : ");
                        scanf(" %[^\n]", temp->designation);

                        saveEmployees();
                        break;

                    case 4:

                        while(1)
                        {
                            printf("New Phone : ");
                            scanf("%s", temp->phone);

                            valid = 1;

                            if(strlen(temp->phone) != 11)
                                valid = 0;

                            for(i = 0; temp->phone[i] != '\0'; i++)
                            {
                                if(!isdigit(temp->phone[i]))
                                {
                                    valid = 0;
                                    break;
                                }
                            }

                            if(valid)
                                break;

                            printf("Invalid Phone Number! Enter 11 digits.\n");
                        }

                        saveEmployees();
                        break;

                    case 5:

                        while(1)
                        {
                            printf("New Email : ");
                            scanf("%s", temp->email);

                            if(strchr(temp->email,'@') != NULL)
                                break;

                            printf("Invalid Email! '@' is required.\n");
                        }

                        saveEmployees();
                        break;

                    case 6:

                        while(1)
                        {
                            printf("New Basic Salary : ");
                            scanf("%f",&temp->basicSalary);

                            if(temp->basicSalary > 0)
                                break;

                            printf("Invalid Basic Salary!\n");
                        }

                        saveEmployees();
                        break;

                    case 7:

                        while(1)
                        {
                            printf("New Password : ");
                            scanf("%s", temp->password);

                            if(strlen(temp->password) >= 4)
                                break;

                            printf("Password Must Be At Least 4 Characters.\n");
                        }

                        saveEmployees();
                        break;

                    case 8:
                        return;

                    default:
                        printf("\nInvalid Choice.\n");
                        continue;
                }

                printf("\nUpdated Successfully.\n");
                logActivity("Employee Updated");
            }
        }

        temp = temp->next;
    }

    printf("\nEmployee Not Found.\n");
}

void deleteEmployee()
{
    int id;

    Employee *temp = head;
    Employee *prev = NULL;

    if(head == NULL)
    {
        printf("\nNo Employee Found.\n");
        return;
    }

    printf("\nEnter Employee ID : ");
    scanf("%d",&id);

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            if(prev == NULL)
            {
                head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }

            free(temp);

deleteAttendanceRecord(id);
deleteLeaveRecord(id);
deleteSalaryRecord(id);
deleteLoanRecord(id);
saveEmployees();

logActivity("Employee Deleted");

printf("\nEmployee Deleted Successfully.\n");

return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\nEmployee Not Found.\n");
}
int employeeExists(int id)
{
    Employee *temp = head;

    while(temp != NULL)
    {
        if(temp->id == id)
            return 1;

        temp = temp->next;
    }

    return 0;
}
void loadEmployees()
{
    FILE *fp = fopen("data/employee.txt","r");

    if(fp == NULL)
        return;

    while(1)
    {
        Employee *newEmployee = (Employee*)malloc(sizeof(Employee));

        if(fscanf(fp,"%d|%99[^|]|%99[^|]|%99[^|]|%19[^|]|%99[^|]|%f|%49[^\n]\n",
            &newEmployee->id,
            newEmployee->name,
            newEmployee->department,
            newEmployee->designation,
            newEmployee->phone,
            newEmployee->email,
            &newEmployee->basicSalary,
            newEmployee->password) != 8)
        {
            free(newEmployee);
            break;
        }

        newEmployee->next = NULL;

        if(head == NULL)
        {
            head = newEmployee;
        }
        else
        {
            Employee *temp = head;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = newEmployee;
        }
    }

    fclose(fp);
}