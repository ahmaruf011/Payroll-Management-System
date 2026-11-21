#ifndef LEAVE_H
#define LEAVE_H

typedef struct Leave
{
    int employeeID;
    char fromDate[20];
    char toDate[20];
    char reason[100];
    char status[20];

    struct Leave *next;

} Leave;

void leaveManagement();

void applyLeave(int employeeID);
void viewPendingLeave();
void approveLeave();
void rejectLeave();
void leaveHistory();
void myLeaveHistory(int employeeID);
void saveLeave();
void loadLeave();
extern Leave *frontLeave;
extern Leave *rearLeave;
void deleteLeaveRecord(int employeeID);

#endif