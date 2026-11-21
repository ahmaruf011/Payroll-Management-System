#ifndef SALARY_H
#define SALARY_H

typedef struct Salary
{
    int employeeID;

    float basicSalary;

    float attendanceBonus;

    float bonus;

    float overtime;

    float tax;

    float providentFund;

    float loanEMI;
    float loanInterest;

    float deduction;

    float grossSalary;
    float netSalary;

    char month[20];

    struct Salary *next;
}Salary;

void salaryManagement();

void addSalary();
void viewSalary();
void searchSalary();
void updateSalary();
void deleteSalary();
void salarySlip();
void mySalarySlip(int employeeID);
void saveSalary();
void loadSalary();
extern Salary *top;
void salaryHistory();
void salaryStatistics();
void monthlySalaryReport();
void highestLowestSalary();
void employeeSalaryHistory();
void salaryIncrement();
void deleteSalaryRecord(int employeeID);
#endif