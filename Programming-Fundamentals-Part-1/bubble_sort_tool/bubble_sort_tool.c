#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

#define EPSILON 1e-13

void bubbleSort(double arr[], int n, int direction) {
    int i, j;
    double temp;
    int swapped; 

    for (i = 0; i < n - 1; i++) {
        swapped = 0; 
        
        for (j = 0; j < n - i - 1; j++) {
            
            int shouldSwap = 0;
            
            if (direction == 1) { 
                if ((arr[j] - arr[j + 1]) > EPSILON) { 
                    shouldSwap = 1;
                }
            } else { 
                if ((arr[j + 1] - arr[j]) > EPSILON) {
                    shouldSwap = 1;
                }
            }

            if (shouldSwap) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1; 
            }
        }
        if (swapped == 0)
            break;
    }
}

void printArray(double arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%.15lf ", arr[i]); 
    }
    printf("\n");
}

double getRandomDouble() {
    int sign = rand() % 2; 
    int int_part = rand() % 1000;
    double frac_part = (double)rand() / (double)RAND_MAX;
    double num = (double)int_part + frac_part;
    
    if (sign == 1) {
        num = -num;
    }
    
    return num;
}


int main(void) {
    srand(time(NULL)); 

    char key;
    
    do {
        int n; 
        double arr[256]; 
        int mode; 
        int sort_dir; 
        
        printf("--- Впорядковувач (Сортування Бульбашкою) ---\n");
        
        printf("Скільки елементів буде у вашому масиві? Введіть число в діапазоні від 1 до 256 ");
        if (scanf("%d", &n) != 1 || n <= 0 || n > 256) {
            printf("Помилка: введіть число від 1 до 256.\n");
            while(getchar() != '\n'); 
            key = 10;
            continue;
        }

        printf("Оберіть вид вводу:\n1) Вручну\n2) Рандом\n");
        scanf("%d", &mode);

        if (mode == 1) { 
            printf("Введіть %d дійсних чисел (напр., 10.5):\n", n);
            for (int i = 0; i < n; i++) {
                printf("Елемент %d: ", i);
                while (scanf("%lf", &arr[i]) != 1) {
                    printf("Помилка! Введіть дійсне число: ");
                    while(getchar() != '\n');
                }
            }
        } else if (mode == 2) { 
            printf("Згенерований масив:\n");
            for (int i = 0; i < n; i++) {
                arr[i] = getRandomDouble();
            }
            printArray(arr, n); 
        } else {
            printf("Помилка: невірний режим вводу.\n");
            while(getchar() != '\n');
            key = 10; 
            continue;
        }

        printf("Оберіть сортування:\n1) За зростанням\n2) За спаданням\n");
        scanf("%d", &sort_dir);

        if (sort_dir != 1 && sort_dir != 2) {
            printf("Помилка: невірний тип сортування.\n");
            while(getchar() != '\n');
            key = 10; 
            continue;
        }

        bubbleSort(arr, n, sort_dir);

        if (sort_dir == 1) {
            printf("Сортування за зростанням:\n");
        } else {
            printf("Сортування за спаданням:\n");
        }
        printArray(arr, n);

        printf("\nНатисніть Enter для повтору або Q+Enter для виходу...\n");
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 
        
        key = getchar();

        if (key != '\n' && key != EOF) { 
            while ((c = getchar()) != '\n' && c != EOF); 
        }

    } while (key == 10); 
    
    return 0;
}