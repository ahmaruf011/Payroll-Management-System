#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/loan.h"
#include "../include/employee.h"
#include "../include/activity.h"
#include "../include/utils.h"

Loan *loanHead = NULL;

void saveLoan()
{
    FILE *fp = fopen("data/loan.txt", "w");

    if(fp == NULL)
        return;

    Loan *temp = loanHead;

    while(temp != NULL)
    {
        fprintf(fp,
      "%d|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%d|%s|%s\n",

        temp->employeeID,
        temp->loanAmount,
        temp->interestRate,
        temp->interest,
        temp->totalPayable,
        temp->monthlyEMI,
        temp->remainingAmount,
        temp->duration,
        temp->reason,
        temp->status);

        temp = temp->next;
    }

    fclose(fp);
}

void loadLoan()
{
    FILE *fp = fopen("data/loan.txt", "r");

    if(fp == NULL)
        return;

    while(1)
    {
        Loan *newNode = (Loan*)malloc(sizeof(Loan));

        if(fscanf(fp,
        "%d|%f|%f|%f|%f|%f|%f|%d|%99[^|]|%19[^\n]\n",

        &newNode->employeeID,
        &newNode->loanAmount,
        &newNode->interestRate,
        &newNode->interest,
        &newNode->totalPayable,
        &newNode->monthlyEMI,
        &newNode->remainingAmount,
        &newNode->duration,
        newNode->reason,
        newNode->status) != 10)
        {
            free(newNode);
            break;
        }

        newNode->next = loanHead;
        loanHead = newNode;
    }

    fclose(fp);
}
void applyLoan(int employeeID)
{
    Loan *check = loanHead;

    while(check != NULL)
    {
        if(check->employeeID == employeeID &&
          (strcmp(check->status,"Pending")==0 ||
           strcmp(check->status,"Approved")==0))
        {
            printf("\nYou Already Have An Active Loan.\n");
            return;
        }

        check = check->next;
    }

    Employee *emp = head;

    while(emp != NULL && emp->id != employeeID)
        emp = emp->next;

    if(emp == NULL)
    {
        printf("\nEmployee Not Found.\n");
        return;
    }
    Loan *newNode = (Loan*)malloc(sizeof(Loan));

    int option;
    int duration;

    float loan25 = emp->basicSalary * 0.25;
    float loan30 = emp->basicSalary * 0.30;

    printf("\n========== APPLY LOAN ==========\n");

    printf("Basic Salary : %.2f\n", emp->basicSalary);

    printf("\n1. 25%% Loan (%.2f)\n", loan25);
    printf("2. 30%% Loan (%.2f)\n", loan30);

    printf("\nChoose Option : ");
    scanf("%d",&option);

    if(option==1)
        newNode->loanAmount=loan25;
    else if(option==2)
        newNode->loanAmount=loan30;
    else
    {
        printf("\nInvalid Option.\n");
        free(newNode);
        return;
    }

    printf("\nLoan Duration\n");
    printf("1. 6 Months (7.5%%)\n");
    printf("2. 12 Months (8.5%%)\n");

    printf("\nChoose : ");
    scanf("%d",&duration);

    if(duration==1)
    {
        newNode->duration=6;
        newNode->interestRate=7.5;
    }
    else if(duration==2)
    {
        newNode->duration=12;
        newNode->interestRate=8.5;
    }
    else
    {
        printf("\nInvalid Duration.\n");
        free(newNode);
        return;
    }

    printf("\nReason : ");
    scanf(" %[^\n]",newNode->reason);
    if(strlen(newNode->reason) == 0)
{
    printf("\nReason Cannot Be Empty.\n");
    free(newNode);
    return;
}

    newNode->employeeID = employeeID;

    newNode->interest =
        newNode->loanAmount *
        newNode->interestRate / 100;

    newNode->totalPayable =
        newNode->loanAmount +
        newNode->interest;

    newNode->monthlyEMI =
        newNode->totalPayable /
        newNode->duration;

    newNode->remainingAmount =
        newNode->totalPayable;

    strcpy(newNode->status,"Pending");

    newNode->next = loanHead;
    loanHead = newNode;

    saveLoan();

    printf("\n========== LOAN SUMMARY ==========\n");

    printf("Loan Amount      : %.2f\n",newNode->loanAmount);
    printf("Interest Rate    : %.2f%%\n",newNode->interestRate);
    printf("Interest         : %.2f\n",newNode->interest);
    printf("Total Payable    : %.2f\n",newNode->totalPayable);
    printf("Monthly EMI      : %.2f\n",newNode->monthlyEMI);
    printf("Duration         : %d Months\n",newNode->duration);
    printf("Status           : %s\n",newNode->status);

    printf("\nLoan Applied Successfully.\n");

    logActivity("Loan Applied");
}
void loanHistory(int employeeID)
{
    Loan *temp = loanHead;
    int found = 0;

    printf("\n========== LOAN HISTORY ==========\n");

    while(temp != NULL)
    {
        if(temp->employeeID == employeeID)
        {
            printf("\nEmployee ID      : %d\n", temp->employeeID);
            printf("Loan Amount      : %.2f\n", temp->loanAmount);
            printf("Interest Rate    : %.2f%%\n", temp->interestRate);
            printf("Interest         : %.2f\n", temp->interest);
            printf("Total Payable    : %.2f\n", temp->totalPayable);
            printf("Monthly EMI      : %.2f\n", temp->monthlyEMI);
            printf("Remaining Amount : %.2f\n", temp->remainingAmount);
            printf("Duration         : %d Months\n", temp->duration);
            printf("Reason           : %s\n", temp->reason);
            printf("Status           : %s\n", temp->status);

            found = 1;
        }

        temp = temp->next;
    }

    if(!found)
        printf("\nNo Loan History Found.\n");
}

void viewLoan()
{
    Loan *temp = loanHead;

    if(temp == NULL)
    {
        printf("\nNo Loan Record Found.\n");
        return;
    }

    printf("\n========== ALL LOANS ==========\n");

    while(temp != NULL)
    {
        printf("\nEmployee ID      : %d\n", temp->employeeID);
        printf("Loan Amount      : %.2f\n", temp->loanAmount);
        printf("Interest Rate    : %.2f%%\n", temp->interestRate);
        printf("Interest         : %.2f\n", temp->interest);
        printf("Total Payable    : %.2f\n", temp->totalPayable);
        printf("Monthly EMI      : %.2f\n", temp->monthlyEMI);
        printf("Remaining Amount : %.2f\n", temp->remainingAmount);
        printf("Duration         : %d Months\n", temp->duration);
        printf("Reason           : %s\n", temp->reason);
        printf("Status           : %s\n", temp->status);

        temp = temp->next;
    }
}

void searchLoan()
{
    int id;

    printf("\nEmployee ID : ");
    scanf("%d",&id);

    Loan *temp = loanHead;

    while(temp != NULL)
    {
        if(temp->employeeID == id)
        {
            printf("\nEmployee ID      : %d\n", temp->employeeID);
            printf("Loan Amount      : %.2f\n", temp->loanAmount);
            printf("Interest Rate    : %.2f%%\n", temp->interestRate);
            printf("Interest         : %.2f\n", temp->interest);
            printf("Total Payable    : %.2f\n", temp->totalPayable);
            printf("Monthly EMI      : %.2f\n", temp->monthlyEMI);
            printf("Remaining Amount : %.2f\n", temp->remainingAmount);
            printf("Duration         : %d Months\n", temp->duration);
            printf("Reason           : %s\n", temp->reason);
            printf("Status           : %s\n", temp->status);
            return;
        }

        temp = temp->next;
    }

    printf("\nLoan Record Not Found.\n");
}

void viewPendingLoan()
{
    Loan *temp = loanHead;
    int found = 0;

    printf("\n========== PENDING LOANS ==========\n");

    while(temp != NULL)
    {
        if(strcmp(temp->status,"Pending")==0)
        {
            printf("\nEmployee ID      : %d\n", temp->employeeID);
            printf("Loan Amount      : %.2f\n", temp->loanAmount);
            printf("Interest Rate    : %.2f%%\n", temp->interestRate);
            printf("Total Payable    : %.2f\n", temp->totalPayable);
            printf("Monthly EMI      : %.2f\n", temp->monthlyEMI);
            printf("Duration         : %d Months\n", temp->duration);
            printf("Reason           : %s\n", temp->reason);

            found = 1;
        }

        temp = temp->next;
    }

    if(!found)
        printf("\nNo Pending Loan Found.\n");
}
void approveLoan()
{
    int id;

    printf("\nEmployee ID : ");
    scanf("%d",&id);

    Loan *temp = loanHead;

    while(temp != NULL)
    {
        if(temp->employeeID == id &&
           strcmp(temp->status,"Pending")==0)
        {
            strcpy(temp->status,"Approved");

            saveLoan();

            printf("\nLoan Approved Successfully.\n");

            logActivity("Loan Approved");

            return;
        }

        temp = temp->next;
    }

    printf("\nPending Loan Not Found.\n");
}

void rejectLoan()
{
    int id;

    printf("\nEmployee ID : ");
    scanf("%d",&id);

    Loan *temp = loanHead;

    while(temp != NULL)
    {
        if(temp->employeeID == id &&
           strcmp(temp->status,"Pending")==0)
        {
            strcpy(temp->status,"Rejected");

            saveLoan();

            printf("\nLoan Rejected Successfully.\n");

            logActivity("Loan Rejected");

            return;
        }

        temp = temp->next;
    }

    printf("\nPending Loan Not Found.\n");
}

void deleteLoan()
{
    int id;

    printf("\nEmployee ID : ");
    scanf("%d",&id);
    char confirm;

printf("Are You Sure? (Y/N) : ");
scanf(" %c",&confirm);

if(confirm!='Y' && confirm!='y')
{
    printf("\nDelete Cancelled.\n");
    return;
}

    Loan *temp = loanHead;
    Loan *prev = NULL;

    while(temp != NULL)
    {
        if(temp->employeeID == id)
        {
            if(prev == NULL)
                loanHead = temp->next;
            else
                prev->next = temp->next;

            free(temp);

            saveLoan();

            printf("\nLoan Deleted Successfully.\n");

            logActivity("Loan Deleted");

            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\nLoan Record Not Found.\n");
}

void deleteLoanRecord(int employeeID)
{
    Loan *temp = loanHead;
    Loan *prev = NULL;

    while(temp != NULL)
    {
        if(temp->employeeID == employeeID)
        {
            Loan *deleteNode = temp;

            if(prev == NULL)
            {
                loanHead = temp->next;
                temp = loanHead;
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

    saveLoan();
}

void loanManagement()
{
    int choice;

    while(1)
    {
        clearScreen();
        printf("\n========== LOAN MANAGEMENT ==========\n");

        printf("1. View Pending Loan\n");
        printf("2. Approve Loan\n");
        printf("3. Reject Loan\n");
        printf("4. View All Loan\n");
        printf("5. Search Loan\n");
        printf("6. Delete Loan\n");
        printf("7. Back\n");

        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                viewPendingLoan();
                break;

            case 2:
                approveLoan();
                break;

            case 3:
                rejectLoan();
                break;

            case 4:
                viewLoan();
                break;

            case 5:
                searchLoan();
                break;

            case 6:
                deleteLoan();
                break;

            case 7:
                return;

            default:
                printf("\nInvalid Choice.\n");
        }
        printf("\nPress Enter to Continue...");
getchar();
getchar();
    }
}