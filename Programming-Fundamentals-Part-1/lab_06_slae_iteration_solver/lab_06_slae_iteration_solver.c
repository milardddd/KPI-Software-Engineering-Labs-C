/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #6
 * Topic: Usage of Dynamic Arrays
 *
 * Author: Timofii Rybalko
 * Created: 12/2025
 *
 * Description:
 * A system of linear algebraic equations (SLAE) solver using the Simple
 * Iteration Method. Demonstrates manual allocation and deallocation of 2D
 * dynamic arrays (matrices) and 1D vectors for high-precision mathematical
 * computations.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MIN_SIZE 2
#define MAX_SIZE 10
#define MAX_ITERATIONS 10000
#define MIN_EPSILON 1e-15
#define ZERO_THRESHOLD 1e-15

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

int get_valid_int(const char* prompt, int min_val, int max_val) {
  int value;
  char term;
  int valid = 0;

  do {
    printf("%s", prompt);
    if (scanf("%d%c", &value, &term) != 2 || term != '\n') {
      printf("Error: Invalid input. Enter an integer from %d to %d.\n", min_val,
             max_val);
      clear_input_buffer();
    } else if (value < min_val || value > max_val) {
      printf("Error: Invalid input. Enter an integer from %d to %d.\n", min_val,
             max_val);
    } else {
      valid = 1;
    }
  } while (!valid);

  return value;
}

double get_precision_special() {
  double value;
  int result;
  int valid = 0;

  do {
    printf(
        "Enter precision (max %g) in scientific notation or decimal form "
        "(0.0...1 or %g): ",
        MIN_EPSILON, MIN_EPSILON);
    result = scanf("%lf", &value);

    if (result == 1 && value > 0) {
      if (value >= 1.0) {
        value = pow(10.0, -value);
      }

      if (value < MIN_EPSILON) {
        printf(
            "Error: Precision is too high for double. Enter a number >= %g.\n",
            MIN_EPSILON);
        valid = 0;
      } else {
        valid = 1;
      }
    } else {
      printf("Error: Invalid precision. Please enter a number.\n");
      clear_input_buffer();
      valid = 0;
    }
  } while (!valid);

  clear_input_buffer();
  return value;
}

double get_coeff(const char* prompt) {
  double value;
  char term;
  int valid = 0;

  do {
    printf("%s", prompt);
    if (scanf("%lf%c", &value, &term) != 2 || term != '\n') {
      printf("Error: Invalid input. Please enter a valid number.\n");
      clear_input_buffer();
    } else {
      valid = 1;
    }
  } while (!valid);

  return value;
}

int main() {
  int key;

  do {
    int n, i, j;
    int iteration = 0;
    int valid_matrix = 1;
    double epsilon;
    double max_delta;

    char prompt_buffer[256];
    char coeff_buffer[100];

    printf("\n=== SLAE Solver: Simple Iteration Method ===\n");

    sprintf(prompt_buffer, "Enter matrix size (rows/elements) [%d, %d]:\n",
            MIN_SIZE, MAX_SIZE);
    n = get_valid_int(prompt_buffer, MIN_SIZE, MAX_SIZE);
    epsilon = get_precision_special();

    double** A = (double**)malloc(n * sizeof(double*));
    double* b = (double*)malloc(n * sizeof(double));
    double* x = (double*)malloc(n * sizeof(double));
    double* xp = (double*)malloc(n * sizeof(double));

    if (!A || !b || !x || !xp) return 1;

    for (i = 0; i < n; i++) {
      A[i] = (double*)malloc(n * sizeof(double));
      if (!A[i]) return 1;
    }

    printf("Press Enter to start entering elements, or any key to proceed.\n");
    printf("Enter coefficients:\n");

    for (i = 0; i < n; i++) {
      printf("--- Row %d ---\n", i + 1);
      for (j = 0; j < n; j++) {
        sprintf(coeff_buffer, "  a[%d][%d] [-2147483646, 2147483646]: ", i + 1,
                j + 1);
        A[i][j] = get_coeff(coeff_buffer);
      }

      sprintf(coeff_buffer, "  b[%d]     [-2147483646, 2147483646]: ", i + 1);
      b[i] = get_coeff(coeff_buffer);

      if (fabs(A[i][i]) < ZERO_THRESHOLD) {
        printf("Error: Diagonal element is too close to zero (< %g).\n",
               ZERO_THRESHOLD);
        valid_matrix = 0;
        break;
      }
    }

    if (valid_matrix) {
      for (i = 0; i < n; i++) {
        xp[i] = b[i] / A[i][i];
      }

      do {
        iteration++;
        max_delta = 0.0;

        for (i = 0; i < n; i++) {
          double sum = 0.0;
          for (j = 0; j < n; j++) {
            if (i != j) {
              sum += A[i][j] * xp[j];
            }
          }
          x[i] = (b[i] - sum) / A[i][i];
          double delta = fabs(x[i] - xp[i]);
          if (delta > max_delta) max_delta = delta;
        }

        for (i = 0; i < n; i++) xp[i] = x[i];

        if (iteration > MAX_ITERATIONS) {
          printf("Iteration limit (%d) reached.\n", MAX_ITERATIONS);
          break;
        }
      } while (max_delta >= epsilon);

      printf("\nResult:\n");
      for (i = 0; i < n; i++) {
        printf("  x%d = %.12lf\n", i + 1, x[i]);
      }
    }

    for (i = 0; i < n; i++) free(A[i]);
    free(A);
    free(b);
    free(x);
    free(xp);

    printf("\nPress Enter to repeat or Q+Enter to exit...\n");
    key = getchar();
    if (key != '\n') {
      int c;
      while ((c = getchar()) != '\n' && c != EOF);
    }

  } while (key == '\n');

  return 0;
}