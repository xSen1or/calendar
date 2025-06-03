//
// Created by jimma on 6/1/2025.
//

#include "cal.h"

#include <stdbool.h>
#include <stdio.h>


int isLeapYear( int year, bool isGregorian) {
    if (isGregorian) {
        return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    } else {
        return (year % 4 == 0);
    }
}

int getDaysInMonth(int month, int year) {
    const int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool isGregorian = false;

    if (year > 1752 || (year == 1752 && month >= 9))
        isGregorian = true;

    int days = days_in_month[month - 1];
    if (month == 2 && isLeapYear(year, isGregorian)) {
        days = 29;
    }
    return days;
}

int getWeekday(int day, int month, int year) {
    if (month < 3) {
        month += 12;
        year--;
    }
    int K = year % 100;
    int J = year / 100;
    int h = (day + 13*(month + 1)/5 + K + K/4 + J/4 + 5*J) % 7;
    return (h + 6) % 7;
}

void printMonth(int month, int year) {
    char *monthName[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    printf("     %s %d\n", monthName[month - 1], year);
    printf("Su Mo Tu We Th Fr Sa\n");

    int days = getDaysInMonth(month, year);
    int start_day = getWeekday(1, month, year);

    for (int i = 0; i < start_day; i++)
        printf("   ");

    for (int day = 1; day <= days; day++) {
        printf("%2d ", day);
        if ((start_day + day) % 7 == 0)
            printf("\n");
    }
    printf("\n\n");
}

void printYearCalendar(int year) {
    for (int row = 0; row < 4; row++) {
        for (int line = 0; line < 8; line++) {
            for (int column = 0; column < 3; column++) {
                int month = row * 3 + column + 1;
                int start_day = getWeekday(1, month, year);
                int days = getDaysInMonth(month, year);

                static char *monthName[] = {
                    "January", "February", "March", "April", "May", "June",
                    "July", "August", "September", "October", "November", "December"
                };

                if (line == 0) {
                    printf("     %-10s      ", monthName[month - 1]);
                } else if (line == 1) {
                    printf("Su Mo Tu We Th Fr Sa  ");
                } else {
                    int day_line = line - 2;
                    int day;
                    int printed = 0;
                    for (int i = 0; i < 7; i++) {
                        day = day_line * 7 + i - start_day + 1;
                        if (day > 0 && day <= days) {
                            printf("%2d ", day);
                        } else {
                            printf("   ");
                        }
                        printed++;
                    }
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("\n");
    }
}

int get_dow(int day, int month, int year) {
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > getDaysInMonth(month, year))
    return 0;

    if (month < 3) {
        month += 12;
        year -= 1;
    }

    bool isGregorian = false;

    if (year > 1752 || (year == 1752 && (month > 9 || (month == 9 && day >= 14)))) {
        isGregorian = true;
    } else if (year == 1752 && month == 9 && day >= 3 && day <= 13) {
        return 0;
    }

    int weak;

    if (isGregorian) {
        weak = (day + (13 * (month + 1)) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
    } else {
        weak = (day + (13 * (month + 1)) / 5 + year + year / 4 + 5) % 7;
    }

    weak = (weak + 6) % 7 + 1;
    return weak;
}

void cal(int month, int year) {
    if (month == 0) {
        for (int month = 1; month <= 12; month++) {
            printMonth(month, year);
        }
    } else if (month >= 1 && month <= 12) {
        printMonth(month, year);
    } else {
        printf("Invalid month for calendar printing\n");
    }
}

void displayCal() {
    int day, month, year;
    while (1) {
        printf("Enter year (>0): ");
        if (scanf("%d", &year) != 1 || year < 1) {
            printf("Invalid year. Try again.\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    while (1) {
        printf("Enter month (1-12, 0 for whole year): ");
        if (scanf("%d", &month) != 1 || month < 0 || month > 12) {
            printf("Invalid month. Try again.\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    cal(month, year);
}

void executeCal() {
    displayCal();
}