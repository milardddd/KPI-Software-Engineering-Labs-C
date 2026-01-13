/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #1
 * Topic: C Program Structure and IDE Fundamentals
 *
 * Author: Timofii Rybalko
 * Created: 09/2025
 *
 * Description:
 * Introduction to C syntax and cross-platform development.
 * Implementation of a decimal to Roman numeral conversion algorithm.
 */

#include <stdio.h>

int roman(int i, int j, char c);

int main() {
  int a;

  printf("Enter a number: ");
  if (scanf("%d", &a) != 1) {
    return 1;
  }

  a = roman(a, 1000, 'M');
  a = roman(a, 500, 'D');
  a = roman(a, 100, 'C');
  a = roman(a, 50, 'L');
  a = roman(a, 10, 'X');
  a = roman(a, 5, 'V');
  a = roman(a, 1, 'I');

  printf("\n\nPress Enter to exit...");

  while (getchar() != '\n');
  getchar();

  return 0;
}

int roman(int i, int j, char c) {
  while (i >= j) {
    putchar(c);
    i = i - j;
  }
  return (i);
}