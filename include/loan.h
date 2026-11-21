#ifndef LOAN_H
#define LOAN_H

typedef struct Loan
{
    int employeeID;

    float loanAmount;
    float interestRate;
    float interest;
    float totalPayable;
    float monthlyEMI;
    float remainingAmount;

    int duration;

    char reason[100];
    char status[20];

    struct Loan *next;

} Loan;

extern Loan *loanHead;

/* File */
void saveLoan();
void loadLoan();

/* Employee */
void applyLoan(int employeeID);
void loanHistory(int employeeID);

/* Admin */
void viewLoan();
void searchLoan();
void viewPendingLoan();
void approveLoan();
void rejectLoan();
void deleteLoan();

/* Menu */
void loanManagement();

/* Helper */
void deleteLoanRecord(int employeeID);

#endif