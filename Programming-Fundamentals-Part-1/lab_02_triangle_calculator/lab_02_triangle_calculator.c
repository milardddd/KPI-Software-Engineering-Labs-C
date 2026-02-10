/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #2
 * Topic: Programming Linear Algorithms
 *
 * Author: Timofii Rybalko
 * Created: 10/2025
 *
 * Description:
 * A triangle geometry calculator that computes Area, Perimeter, Heights,
 * Medians, and Bisectors. Features robust input validation to ensure
 * triangle existence and data range compliance.
 */

#include <math.h>
#include <stdio.h>

int main() {
  char key;

  do {
    printf(
        "This program calculates: Area(S), Perimeter(p), Heights(h), "
        "Bisectors(b), Medians(m)\n");
    printf("\nThe program accepts only numbers from 0.001 to 1000\n");

    double a, b, c;

    printf("Enter side a: ");
    while (scanf("%lf", &a) != 1 || a < 0.001 || a > 1000) {
      printf("Error! Enter side a from 0.001 to 1000: ");
      while (getchar() != '\n');
    }
    while (getchar() != '\n');

    printf("Enter side b: ");
    while (scanf("%lf", &b) != 1 || b < 0.001 || b > 1000) {
      printf("Error! Enter side b from 0.001 to 1000: ");
      while (getchar() != '\n');
    }
    while (getchar() != '\n');

    printf("Enter side c: ");
    while (scanf("%lf", &c) != 1 || c < 0.001 || c > 1000) {
      printf("Error! Enter side c from 0.001 to 1000: ");
      while (getchar() != '\n');
    }
    while (getchar() != '\n');

    if (a <= 0 || b <= 0 || c <= 0 || (a + b) <= c || (a + c) <= b ||
        (b + c) <= a) {
      printf("\nThe triangle does not exist!\n");
    } else {
      double p = (a + b + c) / 2.0;
      double S = sqrt(p * (p - a) * (p - b) * (p - c));

      double ha = 2.0 * S / a;
      double hb = 2.0 * S / b;
      double hc = 2.0 * S / c;

      double ma = 0.5 * sqrt(2 * b * b + 2 * c * c - a * a);
      double mb = 0.5 * sqrt(2 * a * a + 2 * c * c - b * b);
      double mc = 0.5 * sqrt(2 * a * a + 2 * b * b - c * c);

      double ba = 2.0 * sqrt(b * c * p * (p - a)) / (b + c);
      double bb = 2.0 * sqrt(a * c * p * (p - b)) / (a + c);
      double bc = 2.0 * sqrt(a * b * p * (p - c)) / (a + b);

      printf("\n--- Results ---\n");
      printf("Area:      %.15lf\n", S);
      printf("Perimeter: %.15lf\n", 2 * p);
      printf("Heights:    ha=%.15lf hb=%.15lf hc=%.15lf\n", ha, hb, hc);
      printf("Medians:    ma=%.15lf mb=%.15lf mc=%.15lf\n", ma, mb, mc);
      printf("Bisectors:  ba=%.15lf bb=%.15lf bc=%.15lf\n", ba, bb, bc);
    }

    printf("\nPress 'Enter' to repeat or 'Q + Enter' to exit: ");
    key = getchar();
    if (key != '\n') {
      while (getchar() != '\n');
    }
  } while (key == 10);

  return 0;
}