#include <stdio.h>
#include <math.h>

int main() {
    double a, x;

    printf("Введіть значення a: ");
    scanf("%lf", &a);

    if ( a > 0 ) {
        x = -fabs(a - 1) / (2 * a);
    } else {
        x = 0.5 * log (1 + a * a);
    }

    printf("Корінь рівняння: x = %.4lf\n", x);
    
    return 0;
}