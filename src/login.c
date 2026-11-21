#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/login.h"
#include "../include/dashboard.h"
#include "../include/employee.h"
#include "../include/activity.h"
#include "../include/utils.h"
char adminUsername[30] = "admin";
char adminPassword[30] = "";

void adminLogin()
{
    char username[50];
    char password[50];
    int attempt = 0;
    if (adminPassword[0] == '\0') {
        printf("\nAdmin login is not configured. Set PAYROLL_ADMIN_PASSWORD before running.\n");
        return;
    }

    while (attempt < 3)
    {
           clearScreen();
        printf("\n========== ADMIN LOGIN ==========\n");

        printf("Username : ");
        scanf("%49s", username);

        printf("Password : ");
        scanf("%49s", password);

       if(strcmp(username, adminUsername) == 0 &&
   strcmp(password, adminPassword) == 0)
        {
            printf("\nLogin Successful!\n");
            adminDashboard();
            return;
        }

        attempt++;
        printf("\nInvalid Username or Password!\n");
        printf("Remaining Attempt : %d\n",3-attempt);
    }

    printf("\nMaximum Login Attempt Reached!\n");
}
void employeeLogin()
{
    int id;
    char password[50];

    Employee *temp = head;

    printf("\n========== EMPLOYEE LOGIN ==========\n");

    printf("Employee ID : ");
    scanf("%d",&id);

    printf("Password : ");
    scanf("%49s",password);

    while(temp != NULL)
    {
        if(temp->id == id && strcmp(temp->password,password)==0)
        {
            printf("\nLogin Successful.\n");

employeeDashboard(temp);

return;
        }

        temp = temp->next;
    }

    printf("\nInvalid Employee ID or Password.\n");
}
void loadAdmin()
{
    FILE *fp = fopen("data/admin.txt","r");

    if (fp != NULL) {
        if (fscanf(fp, "%29s %29s", adminUsername, adminPassword) != 2)
            adminPassword[0] = '\0';
        fclose(fp);
        return;
    }

    /* Local development credential; never commit real credentials. */
    const char *password = getenv("PAYROLL_ADMIN_PASSWORD");
    if (password != NULL && strlen(password) >= 4 && strlen(password) < sizeof(adminPassword)) {
        strcpy(adminPassword, password);
    }
}
void changeAdminPassword()
{
    char oldPass[30];
    char newPass[30];

    printf("\nCurrent Password : ");
    scanf("%29s", oldPass);

    if(strcmp(oldPass, adminPassword) != 0)
    {
        printf("\nWrong Password.\n");
        return;
    }

    printf("New Password : ");
    scanf("%29s", newPass);

    if(strlen(newPass) < 4)
    {
        printf("\nPassword Must Be At Least 4 Characters.\n");
        return;
    }

    strcpy(adminPassword, newPass);

    FILE *fp = fopen("data/admin.txt", "w");

    if(fp != NULL)
    {
        fprintf(fp, "%s %s", adminUsername, adminPassword);
        fclose(fp);
    }

    printf("\nPassword Changed Successfully.\n");

    logActivity("Admin Password Changed");
}

void changeEmployeePassword(Employee *currentEmployee)
{
    char oldPass[30];
    char newPass[30];

    printf("\nCurrent Password : ");
    scanf("%29s", oldPass);

    if(strcmp(oldPass, currentEmployee->password) != 0)
    {
        printf("\nIncorrect Current Password.\n");
        return;
    }

    printf("New Password : ");
    scanf("%29s", newPass);

    if(strlen(newPass) < 4)
    {
        printf("\nPassword Must Be At Least 4 Characters.\n");
        return;
    }

    strcpy(currentEmployee->password, newPass);

    saveEmployees();

    printf("\nPassword Changed Successfully.\n");

    logActivity("Employee Password Changed");
}