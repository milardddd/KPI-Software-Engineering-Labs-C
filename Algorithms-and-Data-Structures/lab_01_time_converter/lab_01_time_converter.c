/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #1
 * Topic: Linear Algorithms
 *
 * Author: Timofii Rybalko
 * Created: 09/2025
 *
 * Description:
 * Implementation of basic arithmetic operations in C.
 * This program converts a given number of minutes into hours and minutes.
 */

#include <stdio.h>

int main() {
  int minutes, hours, mins;
  printf("Введіть кількість хвилин: ");
  scanf("%d", &minutes);
  hours = minutes / 60;
  mins = minutes % 60;
  printf("%d хвилин = %d год %d хв\n", minutes, hours, mins);
  return 0;
}