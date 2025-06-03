#include <stdbool.h>

#ifndef CAL_H
#define CAL_H

int isLeapYear(int year, bool isGregorian);
int getDaysInMonth(int month, int year);
int get_dow(int day, int month, int year);
void printMonth(int month, int year);
void cal(int month, int year);
void displayCal();
void executeCal();
void printYearCalendar(int year);
int getWeekday(int day, int month, int year);

#endif // CAL_H
