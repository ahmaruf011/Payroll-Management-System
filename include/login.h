#ifndef LOGIN_H
#define LOGIN_H

#include "employee.h"

extern char adminUsername[30];
extern char adminPassword[30];

void adminLogin();
void employeeLogin();

void loadAdmin();
void changeAdminPassword();
void changeEmployeePassword(Employee *currentEmployee);

#endif