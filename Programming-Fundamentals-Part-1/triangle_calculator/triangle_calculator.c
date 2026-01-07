#include <stdio.h> // printf, scanf
#include <math.h> // sqrt корінь

int main() {
    char choice;

    do{
        printf("Це программа яка обчислюе: площу(S), периметр(p), висоти(h), бісектриси(b), медіани(m)\n");
        printf("\nПрограмма приймае тільки числа від 0.001 до 1000\n");

        double a, b, c;

        printf("Введіть сторону a: ");
        while (1) {
            if (scanf("%lf", &a) == 1 && a >= 0.001 && a <= 1000) {
                break; 
            }
            printf("Помилка! Введіть число a від 0.001 до 1000: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n'); 

        printf("Введіть сторону b: ");
        while (1) {
            if (scanf("%lf", &b) == 1 && b >= 0.001 && b <= 1000) {
                break;
            }
            printf("Помилка! Введіть число b від 0.001 до 1000: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        printf("Введіть сторону c: ");
        while (1) {
            if (scanf("%lf", &c) == 1 && c >= 0.001 && c <= 1000) {
                break;
            }
            printf("Помилка! Введіть число c від 0.001 до 1000: ");
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

    
        if (a <= 0 || b <= 0 || c <= 0 || (a+b) <= c || (a+c) <= b || (b+c)  <= a) {
            printf("\nТрикутник не існує!\n");
        } else {
            double p = (a+b+c)/2;
            double S = sqrt(p*(p-a)*(p-b)*(p-c));
            
            double ha = 2.0*S/a;
            double hb = 2.0*S/b;
            double hc = 2.0*S/c;

            double ma = 0.5*sqrt(2*b*b + 2*c*c - a*a);
            double mb = 0.5*sqrt(2*a*a + 2*c*c - b*b);
            double mc = 0.5*sqrt(2*a*a + 2*b*b - c*c);

            double ba = 2.0*sqrt(b*c*p*(p-a))/(b+c);
            double bb = 2.0*sqrt(a*c*p*(p-b))/(a+c);
            double bc = 2.0*sqrt(a*b*p*(p-c))/(a+b);

            printf("Площа: %.15lf\n", S);
            printf("Периметр: %.15lf\n", 2*p);
            printf("Висоти: ha=%.15lf hb=%.15lf hc=%.15lf\n", ha, hb, hc);
            printf("Медіани: ma=%.15lf mb=%.15lf mc=%.15lf\n", ma, mb, mc);
            printf("Бісектриси: ba=%.15lf bb=%.15lf bc=%.15lf\n", ba, bb, bc);
            }

                printf("\nНатисніть Q щоб повторити або Enter для виходу: ");
                choice = getchar();
                while (getchar() != '\n');
        } while (choice == 'Q' || choice == 'q');
    return 0;
}