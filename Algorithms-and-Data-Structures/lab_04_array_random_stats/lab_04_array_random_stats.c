/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #4
 * Topic: Auxiliary Algorithms (Functions & Functional Decomposition)
 *
 * Author: Timofii Rybalko
 * Created: 11/2025
 *
 * Description:
 * Demonstrates the use of functions to perform repetitive tasks on arrays.
 * Includes random data generation, array output, and statistical calculations.
 * Tasks: Fill three arrays (A, B, C) based on user input 'x' and calculate
 * the ratio: |Sum of Negative| / Sum of Positive.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 17

void fillArray(double arr[], double x);
void printArray(double arr[]);
double calcRatio(double arr[]);

int main() {
  srand(time(NULL));

  double A[N], B[N], C[N];
  double xA, xB, xC;

  printf("Введіть х для масиву А: ");
  scanf("%lf", &xA);
  printf("Введіть х для масиву В: ");
  scanf("%lf", &xB);
  printf("Введіть х для масиву С: ");
  scanf("%lf", &xC);

  fillArray(A, xA);
  fillArray(B, xB);
  fillArray(C, xC);

  printf("\nМасив А:\n");
  printArray(A);
  printf("Відношення сума від'ємних / сума додатних = %.31f\n", calcRatio(A));
  printf("\nMасив В:\n");
  printArray(B);
  printf("Відношення сума від'ємних / сума додатних = %.31f\n", calcRatio(B));
  printf("\nMасив С:\n");
  printArray(C);
  printf("Відношення сума від'ємних / сума додатних = %.31f\n", calcRatio(C));

  return 0;
}

void fillArray(double arr[], double x) {
  for (int i = 0; i < N; i++) {
    double range = 9 * x;
    arr[i] = -5 * x + ((double)rand() / RAND_MAX) * range;
  }
}

void printArray(double arr[]) {
  for (int i = 0; i < N; i++) {
    printf("%8.31f", arr[i]);
  }
  printf("\n");
}

double calcRatio(double arr[]) {
  double sumNeg = 0, sumPos = 0;
  for (int i = 0; i < N; i++) {
    if (arr[i] < 0)
      sumNeg += arr[i];
    else
      sumPos += arr[i];
  }

  if (sumPos == 0) return 0;
  return fabs(sumNeg) / sumPos;
}