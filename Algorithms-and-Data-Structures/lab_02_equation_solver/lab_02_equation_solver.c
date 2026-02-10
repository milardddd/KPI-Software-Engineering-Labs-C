/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #2
 * Topic: Branching Algorithms (Selection Statements)
 *
 * Author: Timofii Rybalko
 * Created: 09/2025
 *
 * Description:
 * Evaluation of a piecewise mathematical function.
 * Demonstrates the use of 'if-else' structures and the <math.h> library.
 */

#include <math.h>
#include <stdio.h>

int main() {
  double a, x;

  printf("Введіть значення a: ");
  scanf("%lf", &a);

  if (a > 0) {
    x = -fabs(a - 1) / (2 * a);
  } else {
    x = 0.5 * log(1 + a * a);
  }

  printf("Корінь рівняння: x = %.4lf\n", x);

  return 0;
}