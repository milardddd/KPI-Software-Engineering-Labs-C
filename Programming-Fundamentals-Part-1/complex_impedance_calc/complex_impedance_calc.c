#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
            printf("Уведене значення некоректне або виходить за межі (має бути > 0).\n\n");
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
            printf("Невідома схема\n");
            break;
    }
}

void print_menu_with_schemes() {
    printf("\nОберіть номер контуру:\n");
    
    printf("\n--- 1. Послідовно-паралельний (R || LC) ---\n");
    draw_circuit_art(1);
    
    printf("\n--- 2. Послідовний (R - C - L) ---\n");
    draw_circuit_art(2);
    
    printf("\n--- 3. Складний контур 1 ---\n");
    draw_circuit_art(3);
    
    printf("\n--- 4. Складний контур 2 ---\n");
    draw_circuit_art(4);
    
    printf("\nВаш вибір (натисніть 1-4): ");
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
    printf("     РОЗРАХУНОК КОМПЛЕКСНОГО ОПОРУ КОНТУРУ\n");
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
        printf("Обрано варіант %d. Введіть параметри:\n", circuit);
        printf("----------------------------------------\n");

        ask_double(&L, "Введіть індуктивність L (мГн) (від %g до %g): ", MIN_VAL, MAX_VAL);
        ask_double(&C, "Введіть ємність C (мкФ) (від %g до %g): ", MIN_VAL, MAX_VAL);

        if (circuit == 3 || circuit == 4) {
            ask_double(&R1, "Введіть опір R1 (Ом) (від %g до %g): ", MIN_VAL, MAX_VAL);
            ask_double(&R2, "Введіть опір R2 (Ом) (від %g до %g): ", MIN_VAL, MAX_VAL);
        } else {
            ask_double(&R, "Введіть опір R (Ом) (від %g до %g): ", MIN_VAL, MAX_VAL);
        }

        int range_valid = 0;
        do {
            ask_double(&f_min, "Початкова частота f_min (від %g до %g): ", MIN_FREQ, MAX_FREQ);
            ask_double(&f_max, "Кінцева частота f_max (від %g до %g): ", MIN_FREQ, MAX_FREQ);
            
            if (f_min > f_max) {
                printf("Помилка: f_min має бути менше або дорівнювати f_max.\n");
            } else {
                range_valid = 1;
            }
        } while (!range_valid);

        ask_double(&step, "Крок зміни частоти df (від %g до %g): ", MIN_VAL, MAX_FREQ);

        f_res = 1.0 / (2.0 * pi_val * sqrt(L * C));
        printf("\nРезонансна частота f0: %f\n", f_res);
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
                    num.real = L / C; num.imag = -(R / wC);
                    den.real = R;     den.imag = wL - one_over_wC;
                    break;
                case 2:
                    num.real = L / C; num.imag = R / wC;
                    den.real = R;     den.imag = wL - one_over_wC;
                    break;
                case 3:
                    num.real = R1 * R2; num.imag = R1 * (wL - one_over_wC);
                    den.real = R1 + R2; den.imag = wL - one_over_wC;
                    break;
                case 4:
                    num.real = (R1 * R2) + (L / C); num.imag = (wL * R1) - (R2 / wC);
                    den.real = R1 + R2;             den.imag = wL - one_over_wC;
                    break;
                default:
                    num.real = 0; num.imag = 0;
                    den.real = 1; den.imag = 0;
                    break;
            }

            Z = divide_complex(num, den);
            printf("f = %-10.2f Z = ", f);
            print_complex(Z);

            f += step; 
        }

        printf("\nНатисніть Enter для повтору або Q+Enter для виходу...\n");
        key = getchar(); 
        if (key != '\n') {
            clean_buffer();
        }

    } while (key == '\n');

    return 0;
}