#ifndef EMPLOYEE_H
#define EMPLOYEE_H

typedef struct Employee
{
    int id;
    char name[100];
    char department[100];
    char designation[100];
    char phone[20];
    char email[100];
    float basicSalary;
    char password[50];

    struct Employee *next;

} Employee;

void employeeManagement();
void addEmployee();
void viewEmployees();
void searchEmployee();
void updateEmployee();
void deleteEmployee();
int employeeExists(int id);
void saveEmployees();
void loadEmployees();
extern Employee *head;

#endif