/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #3
 * Topic: Programming Branching Algorithms
 *
 * Author: Timofii Rybalko
 * Created: 11/2025
 *
 * Description:
 * A program that determines the day of the week for any Gregorian calendar
 * date within the range of 1900 to 2099. Uses leap year logic and
 * an iterative algorithm with branching for calculation.
 */

#include <stdio.h>

int main(void) {
#define minYear 1900
#define maxYear 2099

  char key;

  do {
    int day, month, year;
    int n;
    int isLeap;
    int day_of_week;
    char buffer[100];
    char extra;
    int valid_input = 0;

    printf("--- Gregorian Calendar: Day of the Week Finder ---\n");

    do {
      printf("Enter day (1-31): ");
      if (!fgets(buffer, sizeof(buffer), stdin)) continue;

      if (sscanf(buffer, " %d %c", &day, &extra) == 1) {
        if (day >= 1 && day <= 31) {
          valid_input = 1;
        } else {
          printf("Error! Day must be between 1 and 31.\n");
        }
      } else {
        printf("Error! Please enter a valid number.\n");
      }
    } while (!valid_input);

    valid_input = 0;
    do {
      printf("Enter month (1-12): ");
      if (!fgets(buffer, sizeof(buffer), stdin)) continue;

      if (sscanf(buffer, "%d %c", &month, &extra) == 1) {
        if (month >= 1 && month <= 12) {
          valid_input = 1;
        } else {
          printf("Error! Month must be between 1 and 12.\n");
        }
      } else {
        printf("Error! Please enter a valid number.\n");
      }
    } while (!valid_input);

    valid_input = 0;
    do {
      printf("Enter year from %d to %d: ", minYear, maxYear);
      if (!fgets(buffer, sizeof(buffer), stdin)) continue;

      if (sscanf(buffer, "%d %c", &year, &extra) == 1) {
        if (year >= minYear && year <= maxYear) {
          valid_input = 1;
        } else {
          printf("Error! Year must be between %d and %d.\n", minYear, maxYear);
        }
      } else {
        printf("Error! Please enter a valid number.\n");
      }
    } while (!valid_input);

    isLeap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));

    if (month > 2)
      n = 0;
    else if (isLeap)
      n = 1;
    else
      n = 2;

    day_of_week = ((int)(365.25 * year) + (int)(30.56 * month) + day + n) % 7;

    printf("Result: ");
    switch (day_of_week) {
      case 0:
        printf("Monday\n");
        break;
      case 1:
        printf("Tuesday\n");
        break;
      case 2:
        printf("Wednesday\n");
        break;
      case 3:
        printf("Thursday\n");
        break;
      case 4:
        printf("Friday\n");
        break;
      case 5:
        printf("Saturday\n");
        break;
      case 6:
        printf("Sunday\n");
        break;
    }

    printf("\nPress 'Enter' to repeat or 'Q+Enter' to exit...\n");

    if (!fgets(buffer, sizeof(buffer), stdin)) break;
    key = buffer[0];

  } while (key == 10);

  return 0;
}