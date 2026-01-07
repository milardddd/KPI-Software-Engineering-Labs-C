#include <stdio.h>
#include <math.h>
#include <conio.h>

int main()
{
    int key;
    do
    {
        printf("Ця програма обчислює суму ряду:\n");
        double x, eps;
        do
        {
            printf("Введіть x (|x| < 1, x ≠ 0): ");
            scanf("%lf", &x);
            if (x == 0 || fabs(x) >= 1)
            {
printf("Помилка: ряд не сходиться при x = 0 або |x| >= 1, спробуйте
ще раз.\n");
            }
        } while (x == 0 || fabs(x) >= 1);
        do
        {
            printf("Введіть точність eps (eps > 0): ");
            scanf("%lf", &eps);
            if (eps <= 0)
            {
                printf("Помилка: eps має бути додатнім числом!\n");
            }
        } while (eps <= 0);
        double S = 0.0, term;

        int N = 0;
        do
        {
            term = pow(-1.0, N) * pow(x, 2 * N + 1) / (4.0 * N * N + 8.0 * N + 3.0);
            S += term;
            N++;
        } while (fabs(term) >= eps);
        printf("Сума ряду ≈ %.10f\n", S);
        printf("\nНатисніть Enter для повтору або іншу клавішу щоб вийти...\n");
        key = getch();
    } while (key == 13);
    return 0;
}