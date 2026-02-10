/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #7
 * Topic: Functions and Function Pointers
 *
 * Author: Timofii Rybalko
 * Created: 12/2025
 *
 * Description:
 * A numerical analysis tool for root-finding of non-linear equations.
 * Implements the Bisection Method and Newton's (Tangent) Method using
 * function pointers for high modularity. Features Unix-specific terminal
 * control for seamless user interaction.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MIN_COEFF (-100)
#define MAX_COEFF (100)
#define MIN_EPS 1e-15
#define MAX_EPS 0.1

int getch_unix(void) {
  struct termios oldattr, newattr;
  int ch;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return ch;
}

void clean_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

void ask_double(double* value, char* question, double min, double max) {
  int fail;
  char ch;
  do {
    printf(question, min, max);
    fail = scanf("%lf%c", value, &ch) != 2 || ch != '\n';

    if (!fail) {
      fail = *value < min || *value > max;
    }

    if (!fail) {
      fail = (*value == 0);
    }

    if (fail) {
      printf("Error: The entered value is out of bounds or invalid.\n\n");
      if (ch != '\n') {
        clean_buffer();
      }
    }
  } while (fail);
}

int ask_selection_getch(char* text) {
  int ch;
  printf("%s", text);
  do {
    ch = getch_unix();
  } while (ch != '1' && ch != '2');

  printf("%c\n", ch);
  return ch - '0';
}

int check_interval(double x, double a, double b) {
  if (a < b) {
    return x >= a && x <= b;
  } else {
    return x >= b && x <= a;
  }
}

int check_opposite(double a, double b) {
  return (a > 0 && b < 0) || (a < 0 && b > 0);
}

double equation_cos_sin_inv(double x, double y) {
  return cos(y / x) - 2 * sin(1 / x) + 1 / x;
}

double equation_sin_cos_log(double x, double y) {
  return sin(log(x)) - cos(log(x)) + y * log(x);
}

double half_division(double (*equation)(double, double), double a, double b,
                     double y, double eps) {
  double x = 0;

  if ((*equation)(a, y) * (*equation)(b, y) > 0) {
    return 0;
  }

  while (fabs(b - a) > eps) {
    x = (a + b) / 2.0;
    if ((*equation)(a, y) * (*equation)(x, y) > 0) {
      a = x;
    } else {
      b = x;
    }
  }
  return x;
}

double newton_tangent(double (*equation)(double, double), double a, double b,
                      double y, double eps) {
  double value, derivative, delta, x = b;
  int iter = 0;

  do {
    value = (*equation)(x, y);
    derivative = ((*equation)(x + eps, y) - value) / eps;

    if (fabs(derivative) < 1e-9) {
      break;
    }

    delta = value / derivative;
    x -= delta;

    iter++;

  } while (check_interval(x, a, b) && fabs(delta) > eps && iter <= 1000);

  return x;
}

void print_header() {
  printf("\n=======================================================\n");
  printf("     ROOT-FINDING FOR NON-LINEAR EQUATIONS\n");
  printf("=======================================================\n");
  printf("This program finds approximate roots for f(x)=0\n");
  printf("on a given interval [a, b] with chosen precision.\n");
  printf("-------------------------------------------------------\n");
}

int main(void) {
  setbuf(stdout, NULL);

  int key;

  do {
    int equation, method;
    double a, b, y, eps;
    int precision;

    print_header();

    ask_double(&a, "Enter lower bound 'a' (from %g to %g): ", (double)MIN_COEFF,
               (double)MAX_COEFF);
    ask_double(&b, "Enter upper bound 'b' (from %g to %g): ", (double)MIN_COEFF,
               (double)MAX_COEFF);

    if (check_opposite(a, b) || a == b) {
      if (a == b) {
        printf("Error: The interval cannot be a single point.\n");
      } else {
        printf("Error: The interval cannot cross zero (undefined regions).\n");
      }

      printf("\nPress Enter to retry or Q+Enter to exit...\n");
      key = getchar();
      if (key != '\n') {
        clean_buffer();
      }
      continue;
    }

    ask_double(&y, "Enter coefficient 'y' (from %g to %g): ", (double)MIN_COEFF,
               (double)MAX_COEFF);

    ask_double(&eps, "Enter precision (e.g., 1e-3 or 0.001, from %g to %g): ",
               MIN_EPS, MAX_EPS);

    precision = (int)ceil(-log10(eps));
    if (precision < 0) precision = 0;

    equation = ask_selection_getch(
        "\nSelect the equation to solve:\n"
        "1. cos(y/x) - 2sin(1/x) + 1/x = 0\n"
        "2. sin(ln x) - cos(ln x) + y(ln x) = 0\n"
        "Selection: ");

    double (*func)(double, double);
    if (equation == 1) {
      func = equation_cos_sin_inv;
    } else {
      func = equation_sin_cos_log;
    }

    if (equation == 2 && (a <= 0 || b <= 0)) {
      printf(
          "Error: The interval is outside the function's domain (ln x requires "
          "x > 0).\n");

      printf("\nPress Enter to retry or Q+Enter to exit...\n");
      key = getchar();
      if (key != '\n') {
        clean_buffer();
      }
      continue;
    }

    method = ask_selection_getch(
        "\nSelect resolution method:\n"
        "1. Bisection Method\n"
        "2. Newton's Method (Tangent Method)\n"
        "Selection: ");

    double x;
    if (method == 1) {
      x = half_division(func, a, b, y, eps);
    } else {
      x = newton_tangent(func, a, b, y, eps);
    }

    int found = check_interval(x, a, b);
    if (found && fabs(func(x, y)) > 0.1) {
      found = 0;
    }

    if (found) {
      printf("\nFound root x: %.*lf\n", precision, x);
    } else {
      printf(
          "\nNo root found on the given interval, or multiple roots exist.\n");
    }

    printf("\nPress Enter to repeat or Q+Enter to exit...\n");
    key = getchar();
    if (key != '\n') {
      clean_buffer();
    }

  } while (key == '\n');

  return 0;
}