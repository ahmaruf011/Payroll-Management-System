#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
int dateToNumber(char date[])
{
    int day, month, year;

    sscanf(date, "%d/%d/%d", &day, &month, &year);

    return year * 10000 + month * 100 + day;
}
int isLeapYear(int year)
{
    if((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        return 1;

    return 0;
}

int isValidDate(char date[])
{
    int day, month, year;

    if(sscanf(date,"%d/%d/%d",&day,&month,&year)!=3)
        return 0;

    if(year < 2000 || year > 2100)
        return 0;

    if(month < 1 || month > 12)
        return 0;

    int daysInMonth[] =
    {
        31,28,31,30,31,30,
        31,31,30,31,30,31
    };

    if(isLeapYear(year))
        daysInMonth[1]=29;

    if(day < 1 || day > daysInMonth[month-1])
        return 0;

    return 1;
}