#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/salary.h"
#include "../include/employee.h"
#include "../include/activity.h"
#include "../include/loan.h"
#include "../include/utils.h"

Salary *top = NULL;

void saveSalary()
{
    FILE *fp = fopen("data/salary.txt","w");

    if(fp==NULL)
        return;

    Salary *temp=top;

    while(temp!=NULL)
    {
        fprintf(fp,"%d|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%s\n",
        temp->employeeID,
        temp->basicSalary,
        temp->attendanceBonus,
        temp->bonus,
        temp->overtime,
        temp->tax,
        temp->providentFund,
        temp->loanEMI,
        temp->loanInterest,
        temp->deduction,
        temp->netSalary,
        temp->month);

        temp=temp->next;
    }

    fclose(fp);
}

void loadSalary()
{
    FILE *fp=fopen("data/salary.txt","r");

    if(fp==NULL)
        return;

    while(1)
    {
        Salary *newNode=(Salary*)malloc(sizeof(Salary));

        if(fscanf(fp,"%d|%f|%f|%f|%f|%f|%f|%f|%f|%f|%f|%19[^\n]\n",
          &newNode->employeeID,
          &newNode->basicSalary,
          &newNode->attendanceBonus,
          &newNode->bonus,
          &newNode->overtime,
          &newNode->tax,
          &newNode->providentFund,
          &newNode->loanEMI,
          &newNode->loanInterest,
          &newNode->deduction,
          &newNode->netSalary,
          newNode->month)!=12)
        {
            free(newNode);
            break;
        }

        newNode->next=top;
        top=newNode;
    }

    fclose(fp);
}

void salaryManagement()
{
    int choice;

    while(1)
    {
        clearScreen();
        
        printf("\n========== SALARY MANAGEMENT ==========\n");

      printf("1. Add Salary\n");
printf("2. View Salary\n");
printf("3. Search Salary\n");
printf("4. Update Salary\n");
printf("5. Delete Salary\n");
printf("6. Salary Slip\n");
printf("7. Salary History\n");
printf("8. Salary Statistics\n");
printf("9. Monthly Salary Report\n");
printf("10. Highest & Lowest Salary\n");
printf("11. Employee Salary History\n");
printf("12. Salary Increment\n");
printf("13. Back\n");
        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
{
    case 1:
        addSalary();
        break;

    case 2:
        viewSalary();
        break;

    case 3:
        searchSalary();
        break;

    case 4:
        updateSalary();
        break;

    case 5:
        deleteSalary();
        break;

    case 6:
        salarySlip();
        break;

    case 7:
        salaryHistory();
        break;
        case 8:
    salaryStatistics();
    break;

    case 9:
        monthlySalaryReport();
        break;

    case 10:
    highestLowestSalary();
    break;

case 11:
    employeeSalaryHistory();
    break;

case 12:
    salaryIncrement();
    break;

case 13:
    return;
    default:
        printf("\nInvalid Choice.\n");
}
printf("\nPress Enter to Continue...");
getchar();
getchar();
    }
}
void addSalary()
{
    Salary *newNode = (Salary*)malloc(sizeof(Salary));

    printf("\nEmployee ID : ");
    scanf("%d", &newNode->employeeID);

    if(!employeeExists(newNode->employeeID))
    {
        printf("\nEmployee Not Found.\n");
        free(newNode);

        return;
        
    }

    /* Get Basic Salary From Employee */
    Employee *emp = head;

    while(emp != NULL)
    {
        if(emp->id == newNode->employeeID)
        {
            newNode->basicSalary = emp->basicSalary;
            break;
        }

        emp = emp->next;
    }

    printf("Month (MM/YYYY) : ");
    scanf("%19s", newNode->month);

    /* Validate Month Format */
    if(strlen(newNode->month) != 7 ||
       newNode->month[2] != '/' ||
       newNode->month[0] < '0' || newNode->month[0] > '1' ||
       newNode->month[1] < '0' || newNode->month[1] > '9')
    {
        printf("\nInvalid Month Format!\n");
        printf("Example: 07/2026\n");
        free(newNode);
        return;
    }

    int month = (newNode->month[0]-'0')*10 + (newNode->month[1]-'0');

    if(month < 1 || month > 12)
    {
        printf("\nInvalid Month!\n");
        free(newNode);
        return;
    }

    /* Duplicate Salary Check */
    Salary *temp = top;

    while(temp != NULL)
    {
        if(temp->employeeID == newNode->employeeID &&
           strcmp(temp->month, newNode->month) == 0)
        {
            printf("\nSalary Already Generated For %s.\n", newNode->month);
            free(newNode);
            return;
        }

        temp = temp->next;
    }

    printf("Basic Salary : %.2f\n", newNode->basicSalary);

    printf("Bonus : ");
    scanf("%f", &newNode->bonus);
    printf("Attendance Bonus : ");
scanf("%f", &newNode->attendanceBonus);
newNode->providentFund = newNode->basicSalary * 0.05;
newNode->loanEMI = 0;

newNode->loanInterest = 0;

    printf("Overtime : ");
    scanf("%f", &newNode->overtime);

    printf("Deduction : ");
    scanf("%f", &newNode->deduction);

   newNode->grossSalary =
    newNode->basicSalary +
    newNode->attendanceBonus +
    newNode->bonus +
    newNode->overtime;
    if(newNode->grossSalary >= 50000)
    newNode->tax = newNode->grossSalary * 0.10;
else if(newNode->grossSalary >= 30000)
    newNode->tax = newNode->grossSalary * 0.05;
else
    newNode->tax = 0;


    
    

Loan *loan = loanHead;

while(loan != NULL)
{
    if(loan->employeeID == newNode->employeeID &&
       strcmp(loan->status,"Approved")==0)
    {
        newNode->loanEMI = loan->monthlyEMI;
        newNode->loanInterest = 0;

        loan->remainingAmount -= loan->monthlyEMI;

        if(loan->remainingAmount <= 0)
        {
            loan->remainingAmount = 0;
            strcpy(loan->status,"Completed");

            logActivity("Loan Completed");
        }

        saveLoan();

        break;
    }

    loan = loan->next;
}

saveLoan();
newNode->netSalary =
    newNode->grossSalary
    - newNode->tax
    - newNode->providentFund
    - newNode->loanEMI
    - newNode->loanInterest
    - newNode->deduction;
    
    newNode->next = top;
    top = newNode;

    saveSalary();

    printf("\nSalary Added Successfully.\n");
    logActivity("Salary Added");
}
void viewSalary()
{
    Salary *temp = top;

    if(temp == NULL)
    {
        printf("\nNo Salary Record Found.\n");
        return;
    }

    printf("\n");
    printf("====================================================================================================\n");
    printf("                                      SALARY LIST\n");
    printf("====================================================================================================\n");

    printf("%-8s %-12s %-16s %-16s %-16s %-18s %-16s\n",
           "ID",
           "Month",
           "Basic Salary",
           "Total Bonus",
           "Gross Salary",
           "Total Deduction",
           "Net Salary");

    printf("----------------------------------------------------------------------------------------------------\n");

    while(temp != NULL)
    {
        float totalBonus;
        float totalDeduction;

        /* All Bonus */
        totalBonus =
            temp->attendanceBonus +
            temp->bonus +
            temp->overtime;

        /* All Deduction */
        totalDeduction =
            temp->tax +
            temp->providentFund +
            temp->loanEMI +
            temp->loanInterest +
            temp->deduction;

        printf("%-8d %-12s %-16.2f %-16.2f %-16.2f %-18.2f %-16.2f\n",
               temp->employeeID,
               temp->month,
               temp->basicSalary,
               totalBonus,
               temp->grossSalary,
               totalDeduction,
               temp->netSalary);

        temp = temp->next;
    }

    printf("====================================================================================================\n");
}
void searchSalary()
{
    int id;

    Salary *temp = top;

    printf("\nEnter Employee ID : ");
    scanf("%d",&id);

    while(temp != NULL)
    {
        printf("\nEmployee ID      : %d\n", temp->employeeID);
printf("Month            : %s\n", temp->month);
        if(temp->employeeID == id)
        {
            printf("\nEmployee ID       : %d\n", temp->employeeID);
printf("Month             : %s\n", temp->month);
printf("Basic Salary      : %.2f\n", temp->basicSalary);
printf("Attendance Bonus  : %.2f\n", temp->attendanceBonus);
printf("Bonus             : %.2f\n", temp->bonus);
printf("Overtime          : %.2f\n", temp->overtime);
printf("Gross Salary      : %.2f\n", temp->grossSalary);
printf("Tax               : %.2f\n", temp->tax);
printf("Provident Fund    : %.2f\n", temp->providentFund);
printf("Loan EMI          : %.2f\n", temp->loanEMI);
printf("Loan Interest     : %.2f\n", temp->loanInterest);
printf("Deduction         : %.2f\n", temp->deduction);
printf("Net Salary        : %.2f\n", temp->netSalary);
            return;
        }

        temp = temp->next;
    }

    printf("\nSalary Record Not Found.\n");
}
void updateSalary()
{
    int id;
char month[20];
    Salary *temp = top;

    printf("\nEnter Employee ID : ");
    scanf("%d",&id);
    printf("Enter Month (MM/YYYY) : ");
scanf("%19s",month);

    while(temp != NULL)
    {
        if(temp->employeeID == id &&
   strcmp(temp->month,month)==0)
        {
            printf("New Attendance Bonus : ");
scanf("%f",&temp->attendanceBonus);

printf("New Bonus : ");
scanf("%f",&temp->bonus);

printf("New Overtime : ");
scanf("%f",&temp->overtime);

printf("New Tax : ");
scanf("%f",&temp->tax);

printf("New Provident Fund : ");
scanf("%f",&temp->providentFund);

printf("New Loan EMI : ");
scanf("%f",&temp->loanEMI);

printf("New Loan Interest : ");
scanf("%f",&temp->loanInterest);

printf("New Deduction : ");
scanf("%f",&temp->deduction);
            temp->grossSalary =
    temp->basicSalary +
    temp->attendanceBonus +
    temp->bonus +
    temp->overtime;

temp->netSalary =
    temp->grossSalary
    - temp->tax
    - temp->providentFund
    - temp->loanEMI
    - temp->loanInterest
    - temp->deduction;
            

            saveSalary();

            printf("\nSalary Updated Successfully.\n");
            logActivity("Salary Updated");
            return;
        }

        temp = temp->next;
    }

    printf("\nSalary Record Not Found.\n");
}
void deleteSalary()
{
    int id;
char month[20];
    Salary *temp = top;
    Salary *prev = NULL;

    printf("\nEnter Employee ID : ");
    scanf("%d",&id);
    printf("Enter Month (MM/YYYY) : ");
scanf("%19s",month);

    while(temp != NULL)
    {
        if(temp->employeeID == id &&
   strcmp(temp->month,month)==0)
        {
            if(prev == NULL)
            {
                top = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }

            free(temp);

            saveSalary();

            printf("\nSalary Deleted Successfully.\n");
            logActivity("Salary Deleted");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\nSalary Record Not Found.\n");
}

void salaryHistory()
{
    int id;

    printf("\nEmployee ID : ");
    scanf("%d",&id);

    Salary *temp=top;
    int found=0;

    while(temp!=NULL)
    {
        if(temp->employeeID==id)
        {
            printf("\nMonth : %s",temp->month);
            printf("\nNet Salary : %.2f\n",temp->netSalary);
            found=1;
        }

        temp=temp->next;
    }

    if(!found)
        printf("\nNo Salary History Found.\n");
}
void salarySlip()
{
    int employeeID;

    printf("\nEnter Employee ID : ");
    scanf("%d", &employeeID);

    mySalarySlip(employeeID);
}
void mySalarySlip(int employeeID)
{
    char month[20];
printf("\n========== MY SALARY SLIP ==========\n");
printf("Enter Month (Example: 08/2026)\n");
printf("Month : ");
scanf("%19s", month);
    Salary *temp = top;

    while(temp != NULL)
    {
        if(temp->employeeID == employeeID &&
           strcmp(temp->month, month) == 0)
        {
            printf("\n==========================================\n");
printf("           MY SALARY SLIP\n");
printf("==========================================\n");
printf("Employee ID       : %d\n", temp->employeeID);
printf("Month             : %s\n", temp->month);

printf("------------------------------------------\n");

printf("Basic Salary      : %.2f\n", temp->basicSalary);
printf("Attendance Bonus  : %.2f\n", temp->attendanceBonus);
printf("Bonus             : %.2f\n", temp->bonus);
printf("Overtime          : %.2f\n", temp->overtime);

printf("------------------------------------------\n");

printf("Gross Salary      : %.2f\n", temp->grossSalary);

printf("------------------------------------------\n");

printf("Tax               : %.2f\n", temp->tax);
printf("Provident Fund    : %.2f\n", temp->providentFund);
printf("Loan EMI          : %.2f\n", temp->loanEMI);
printf("Loan Interest     : %.2f\n", temp->loanInterest);
printf("Other Deduction   : %.2f\n", temp->deduction);

printf("------------------------------------------\n");

printf("Net Salary        : %.2f\n", temp->netSalary);

printf("==========================================\n");
            return;
        }

        temp = temp->next;
    }

    printf("\nSalary Slip Not Found.\n");
}
void salaryStatistics()
{
    Salary *temp = top;

    int totalEmployee = 0;

    float totalSalary = 0;
    float totalBonus = 0;
    float totalOvertime = 0;
    float totalDeduction = 0;

    while(temp != NULL)
    {
        totalEmployee++;

        totalSalary += temp->netSalary;
        totalBonus += temp->bonus;
        totalOvertime += temp->overtime;
        totalDeduction += temp->deduction;

        temp = temp->next;
    }

    printf("\n========== SALARY STATISTICS ==========\n");

    printf("Total Salary Records : %d\n", totalEmployee);
    printf("Total Salary Paid    : %.2f\n", totalSalary);
    printf("Total Bonus          : %.2f\n", totalBonus);
    printf("Total Overtime       : %.2f\n", totalOvertime);
    printf("Total Deduction      : %.2f\n", totalDeduction);

    if(totalEmployee>0)
        printf("Average Salary       : %.2f\n",
               totalSalary/totalEmployee);
}
void monthlySalaryReport()
{
    char month[20];

    printf("\nEnter Month (MM/YYYY) : ");
    scanf("%19s", month);

    Salary *temp = top;

    int found = 0;
    float total = 0;

    printf("\n========== MONTHLY SALARY REPORT ==========\n");

    while(temp != NULL)
    {
        if(strcmp(temp->month, month) == 0)
        {
            printf("\nEmployee ID : %d\n", temp->employeeID);
            printf("Net Salary  : %.2f\n", temp->netSalary);

            total += temp->netSalary;
            found = 1;
        }

        temp = temp->next;
    }

    if(!found)
    {
        printf("\nNo Salary Record Found.\n");
        return;
    }

    printf("\n---------------------------------\n");
    printf("Total Salary Paid : %.2f\n", total);
}
void highestLowestSalary()
{
    if(top == NULL)
    {
        printf("\nNo Salary Record Found.\n");
        return;
    }

    Salary *temp = top;
    Salary *highest = top;
    Salary *lowest = top;

    while(temp != NULL)
    {
        if(temp->netSalary > highest->netSalary)
            highest = temp;

        if(temp->netSalary < lowest->netSalary)
            lowest = temp;

        temp = temp->next;
    }

    printf("\n========== HIGHEST SALARY ==========\n");
    printf("Employee ID : %d\n", highest->employeeID);
    printf("Month       : %s\n", highest->month);
    printf("Net Salary  : %.2f\n", highest->netSalary);

    printf("\n========== LOWEST SALARY ==========\n");
    printf("Employee ID : %d\n", lowest->employeeID);
    printf("Month       : %s\n", lowest->month);
    printf("Net Salary  : %.2f\n", lowest->netSalary);
}
void employeeSalaryHistory()
{
    int id;

    printf("\nEnter Employee ID : ");
    scanf("%d",&id);

    Salary *temp = top;
    int found = 0;

    printf("\n========== EMPLOYEE SALARY HISTORY ==========\n");

    while(temp != NULL)
    {
        if(temp->employeeID == id)
        {
            printf("\nMonth        : %s\n", temp->month);
            printf("Gross Salary : %.2f\n", temp->grossSalary);
            printf("Net Salary   : %.2f\n", temp->netSalary);

            found = 1;
        }

        temp = temp->next;
    }

    if(!found)
        printf("\nNo Salary History Found.\n");
}
void salaryIncrement()
{
    int id;
    float amount;

    printf("\nEmployee ID : ");
    scanf("%d",&id);

    Employee *temp = head;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            printf("Increment Amount : ");
            scanf("%f",&amount);
            if(amount <= 0)
{
    printf("\nInvalid Increment Amount.\n");
    return;
}

            temp->basicSalary += amount;

            saveEmployees();

            printf("\nSalary Increment Added Successfully.\n");

            logActivity("Salary Increment");

            return;
        }

        temp = temp->next;
    }

    printf("\nEmployee Not Found.\n");
}
void deleteSalaryRecord(int employeeID)
{
    Salary *temp = top;
    Salary *prev = NULL;

    while(temp != NULL)
    {
        if(temp->employeeID == employeeID)
        {
            Salary *deleteNode = temp;

            if(prev == NULL)
            {
                top = temp->next;
                temp = top;
            }
            else
            {
                prev->next = temp->next;
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

    saveSalary();
}