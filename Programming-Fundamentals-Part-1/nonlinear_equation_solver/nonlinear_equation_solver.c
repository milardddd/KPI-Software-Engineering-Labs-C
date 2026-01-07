#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
            printf("Уведене значення знаходиться поза межами допустимих або некоректне.\n\n");
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
    return cos(y/x) - 2*sin(1/x) + 1/x;
}

double equation_sin_cos_log(double x, double y) {
    return sin(log(x)) - cos(log(x)) + y*log(x);
}

double half_division(double (*equation)(double, double), double a, double b, double y, double eps) {
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

double newton_tangent(double (*equation)(double, double), double a, double b, double y, double eps) {
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
    printf("     ОБЧИСЛЕННЯ КОРЕНІВ НЕЛІНІЙНИХ РІВНЯНЬ\n");
    printf("=======================================================\n");
    printf("Ця програма знаходить наближені корені рівняння f(x)=0\n");
    printf("на заданому проміжку [a, b] з обраною точністю.\n");
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

        ask_double(&a, "Перша межа 'a' (від %g до %g): ", (double)MIN_COEFF, (double)MAX_COEFF);
        ask_double(&b, "Друга межа 'b' (від %g до %g): ", (double)MIN_COEFF, (double)MAX_COEFF);

        if (check_opposite(a, b) || a == b) {
            if (a == b) {
                printf("Інтервал не може бути заданий одним числом.\n");
            } else {
                printf("Інтервал не може перетинати нуль.\n");
            }
            
            printf("\nНатисніть Enter для повтору або Q+Enter для виходу...\n");
            key = getchar(); 
            if (key != '\n') {
                clean_buffer();
            }
            continue;
        }

        ask_double(&y, "Коефіцієнт 'y' (від %g до %g): ", (double)MIN_COEFF, (double)MAX_COEFF);
        
        ask_double(&eps, "Точність (наприклад 1e-2 або 0.001, від %g до %g): ", MIN_EPS, MAX_EPS);
        
        precision = (int)ceil(-log10(eps)); 
        if (precision < 0) precision = 0;

        equation = ask_selection_getch("\nОберіть розв'язуване рівняння:\n"
                                       "1. cos(y/x) - 2sin(1/x) + 1/x = 0\n"
                                       "2. sin(ln x) - cos(ln x) + y(ln x) = 0\n"
                                       "Ваш вибір: ");
        
        double (*func)(double, double);
        if (equation == 1) {
            func = equation_cos_sin_inv;
        } else {
            func = equation_sin_cos_log;
        }

        if (equation == 2 && (a <= 0 || b <= 0)) {
            printf("Інтервал виходить за область визначення функції.\n");
            
            printf("\nНатисніть Enter для повтору або Q+Enter для виходу...\n");
            key = getchar(); 
            if (key != '\n') {
                clean_buffer();
            }
            continue;
        }

        method = ask_selection_getch("\nОберіть метод розв'язання:\n"
                                     "1. Метод половинного ділення\n"
                                     "2. Метод дотичних (Ньютона)\n"
                                     "Ваш вибір: ");

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
            printf("\nШуканий корінь x: %.*lf\n", precision, x);
        } else {
            printf("\nНа заданому проміжку корінь не визначено, або визначено більше ніж один.\n");
        }

        printf("\nНатисніть Enter для повтору або Q+Enter для виходу...\n");
        key = getchar(); 
        if (key != '\n') {
            clean_buffer();
        }

    } while (key == '\n');

    return 0;
}