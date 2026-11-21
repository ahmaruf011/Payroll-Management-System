#ifndef ATTENDANCE_H
#define ATTENDANCE_H

typedef struct Attendance
{
    int employeeID;
    char date[20];
    char status[20];

    struct Attendance *next;

}Attendance;

void attendanceManagement();
void markAttendance();
void viewAttendance();
void searchAttendance();
void updateAttendance();
void deleteAttendance();
void saveAttendance();
void loadAttendance();
extern Attendance *front;
extern Attendance *rear;
void deleteAttendanceRecord(int id);

#endif