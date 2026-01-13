/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #8
 * Topic: Application of Structures
 *
 * Author: Timofii Rybalko
 * Created: 12/2025
 *
 * Description:
 * A specialized tool for calculating the complex impedance of various RLC
 * circuits. Utilizes custom structures for complex number arithmetic and models
 * four different circuit topologies. Includes resonant frequency analysis and
 * ASCII-based circuit visualization.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MIN_VAL 1e-9
#define MAX_VAL 1e9
#define MIN_FREQ 1e-6
#define MAX_FREQ 1e9

typedef struct {
  double real;
  double imag;
} complex;

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
      fail = (*value <= 0);
    }

    if (fail) {
      printf("Error: Input is invalid or out of bounds (must be > 0).\n\n");
      if (ch != '\n') {
        clean_buffer();
      }
    }
  } while (fail);
}

void draw_circuit_art(int circuit) {
  switch (circuit) {
    case 1:
      printf("          +---[ R ]---UUUUU---+\n");
      printf("          |             L     |\n");
      printf("      0---+                   +---0\n");
      printf("          |                   |\n");
      printf("          +--------||---------+\n");
      printf("                    C          \n");
      break;
    case 2:
      printf("          +---[ R ]----||-----+\n");
      printf("          |            C      |\n");
      printf("      0---+                   +---0\n");
      printf("          |                   |\n");
      printf("          +-------UUUUU-------+\n");
      printf("                    L          \n");
      break;
    case 3:
      printf("            +-----[ R2 ]-----||----+\n");
      printf("            |                 C    |\n");
      printf("       0--+-+                      |\n");
      printf("          | |                      |\n");
      printf("         [R1]                      |\n");
      printf("          | |                      |\n");
      printf("       0--+-+-------UUUUU----------+\n");
      printf("                      L             \n");
      break;
    case 4:
      printf("            +-----[ R1 ]-----||----+\n");
      printf("            |                 C    |\n");
      printf("       0--+-+                      +---0\n");
      printf("            |                      |\n");
      printf("            +-----[ R2 ]----UUUUU--+\n");
      printf("                              L     \n");
      break;
    default:
      printf("Unknown circuit type.\n");
      break;
  }
}

void print_menu_with_schemes() {
  printf("\nSelect the circuit number:\n");

  printf("\n--- 1. Parallel-Series (R || LC) ---\n");
  draw_circuit_art(1);

  printf("\n--- 2. Series (R - C - L) ---\n");
  draw_circuit_art(2);

  printf("\n--- 3. Complex Circuit 1 ---\n");
  draw_circuit_art(3);

  printf("\n--- 4. Complex Circuit 2 ---\n");
  draw_circuit_art(4);

  printf("\nYour selection (press 1-4): ");
}

int ask_selection_getch() {
  int ch;
  do {
    ch = getch_unix();
  } while (ch < '1' || ch > '4');

  printf("%c\n", ch);
  return ch - '0';
}

complex divide_complex(complex num, complex den) {
  complex result;
  double denominator = den.real * den.real + den.imag * den.imag;

  if (denominator == 0) {
    result.real = 0;
    result.imag = 0;
    return result;
  }

  result.real = (num.real * den.real + num.imag * den.imag) / denominator;
  result.imag = (num.imag * den.real - num.real * den.imag) / denominator;
  return result;
}

void print_complex(complex z) {
  if (z.imag >= 0)
    printf("%e + i*%e\n", z.real, z.imag);
  else
    printf("%e - i*%e\n", z.real, -z.imag);
}

void print_header() {
  printf("\n=======================================================\n");
  printf("     CIRCUIT COMPLEX IMPEDANCE CALCULATION\n");
  printf("=======================================================\n");
}

int main(void) {
  setbuf(stdout, NULL);

  const double pi_val = acos(-1.0);
  int key;

  do {
    int circuit;
    double L, C, R = 0, R1 = 0, R2 = 0;
    double f_min, f_max, step, f_res;

    print_header();
    print_menu_with_schemes();
    circuit = ask_selection_getch();

    printf("\n----------------------------------------\n");
    printf("Selected option %d. Enter parameters:\n", circuit);
    printf("----------------------------------------\n");

    ask_double(&L, "Enter inductance L (mH) (from %g to %g): ", MIN_VAL,
               MAX_VAL);
    ask_double(&C, "Enter capacitance C (uF) (from %g to %g): ", MIN_VAL,
               MAX_VAL);

    if (circuit == 3 || circuit == 4) {
      ask_double(&R1, "Enter resistance R1 (Ohm) (from %g to %g): ", MIN_VAL,
                 MAX_VAL);
      ask_double(&R2, "Enter resistance R2 (Ohm) (from %g to %g): ", MIN_VAL,
                 MAX_VAL);
    } else {
      ask_double(&R, "Enter resistance R (Ohm) (from %g to %g): ", MIN_VAL,
                 MAX_VAL);
    }

    int range_valid = 0;
    do {
      ask_double(&f_min, "Initial frequency f_min (from %g to %g): ", MIN_FREQ,
                 MAX_FREQ);
      ask_double(&f_max, "Final frequency f_max (from %g to %g): ", MIN_FREQ,
                 MAX_FREQ);

      if (f_min > f_max) {
        printf("Error: f_min must be less than or equal to f_max.\n");
      } else {
        range_valid = 1;
      }
    } while (!range_valid);

    ask_double(&step, "Frequency step df (from %g to %g): ", MIN_VAL, MAX_FREQ);

    f_res = 1.0 / (2.0 * pi_val * sqrt(L * C));
    printf("\nResonant frequency f0: %f\n", f_res);
    printf("----------------------------------------\n");

    double f = f_min;
    while (f <= f_max) {
      double w = 2.0 * pi_val * f;
      complex Z, num, den;
      double wL = w * L;
      double one_over_wC = 1.0 / (w * C);
      double wC = w * C;

      switch (circuit) {
        case 1:
          num.real = L / C;
          num.imag = -(R / wC);
          den.real = R;
          den.imag = wL - one_over_wC;
          break;
        case 2:
          num.real = L / C;
          num.imag = R / wC;
          den.real = R;
          den.imag = wL - one_over_wC;
          break;
        case 3:
          num.real = R1 * R2;
          num.imag = R1 * (wL - one_over_wC);
          den.real = R1 + R2;
          den.imag = wL - one_over_wC;
          break;
        case 4:
          num.real = (R1 * R2) + (L / C);
          num.imag = (wL * R1) - (R2 / wC);
          den.real = R1 + R2;
          den.imag = wL - one_over_wC;
          break;
        default:
          num.real = 0;
          num.imag = 0;
          den.real = 1;
          den.imag = 0;
          break;
      }

      Z = divide_complex(num, den);
      printf("f = %-10.2f Z = ", f);
      print_complex(Z);

      f += step;
    }

    printf("\nPress Enter to repeat or Q+Enter to exit...\n");
    key = getchar();
    if (key != '\n') {
      clean_buffer();
    }

  } while (key == '\n');

  return 0;
}