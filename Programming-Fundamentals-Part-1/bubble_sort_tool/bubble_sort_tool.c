/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #4
 * Topic: Loop Operators and Array Processing
 *
 * Author: Timofii Rybalko
 * Created: 11/2025
 *
 * Description:
 * A tool for sorting arrays of double-precision floating-point numbers
 * using an optimized Bubble Sort algorithm. Supports manual entry or
 * random generation with precision-based comparison (EPSILON).
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EPSILON 1e-13

void bubbleSort(double arr[], int n, int direction) {
  int i, j;
  double temp;
  int swapped;

  for (i = 0; i < n - 1; i++) {
    swapped = 0;

    for (j = 0; j < n - i - 1; j++) {
      int shouldSwap = 0;

      if (direction == 1) {
        if ((arr[j] - arr[j + 1]) > EPSILON) {
          shouldSwap = 1;
        }
      } else {
        if ((arr[j + 1] - arr[j]) > EPSILON) {
          shouldSwap = 1;
        }
      }

      if (shouldSwap) {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        swapped = 1;
      }
    }
    if (swapped == 0) break;
  }
}

void printArray(double arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%.15lf ", arr[i]);
  }
  printf("\n");
}

double getRandomDouble() {
  int sign = rand() % 2;
  int int_part = rand() % 1000;
  double frac_part = (double)rand() / (double)RAND_MAX;
  double num = (double)int_part + frac_part;

  if (sign == 1) {
    num = -num;
  }

  return num;
}

int main(void) {
  srand(time(NULL));

  char key;

  do {
    int n;
    double arr[256];
    int mode;
    int sort_dir;

    printf("--- Array Sorter (Bubble Sort Tool) ---\n");

    printf("How many elements will be in your array? (1-256): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 256) {
      printf("Error: please enter a number from 1 to 256.\n");
      while (getchar() != '\n');
      key = 10;
      continue;
    }

    printf("Choose input mode:\n1) Manual\n2) Random\nSelection: ");
    scanf("%d", &mode);

    if (mode == 1) {
      printf("Enter %d real numbers (e.g., 10.5):\n", n);
      for (int i = 0; i < n; i++) {
        printf("Element %d: ", i);
        while (scanf("%lf", &arr[i]) != 1) {
          printf("Error! Please enter a valid real number: ");
          while (getchar() != '\n');
        }
      }
    } else if (mode == 2) {
      printf("Generated array:\n");
      for (int i = 0; i < n; i++) {
        arr[i] = getRandomDouble();
      }
      printArray(arr, n);
    } else {
      printf("Error: invalid input mode.\n");
      while (getchar() != '\n');
      key = 10;
      continue;
    }

    printf("Choose sorting order:\n1) Ascending\n2) Descending\nSelection: ");
    scanf("%d", &sort_dir);

    if (sort_dir != 1 && sort_dir != 2) {
      printf("Error: invalid sorting type.\n");
      while (getchar() != '\n');
      key = 10;
      continue;
    }

    bubbleSort(arr, n, sort_dir);

    if (sort_dir == 1) {
      printf("Sorted in ascending order:\n");
    } else {
      printf("Sorted in descending order:\n");
    }
    printArray(arr, n);

    printf("\nPress Enter to repeat or Q+Enter to exit...\n");

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    key = getchar();

    if (key != '\n' && key != EOF) {
      while ((c = getchar()) != '\n' && c != EOF);
    }

  } while (key == 10);

  return 0;
}