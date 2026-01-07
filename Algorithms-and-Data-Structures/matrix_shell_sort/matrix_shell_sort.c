#include <stdio.h> 

#define N 5
#define M 4

void fill_array_A(int A[N][M]);
void print_array_A(int A[N][M], const char* title);
void calculate_array_B(int A[N][M], double B[N]);
void print_array_B(double B[N], const char* title);
void sort_columns_shell(int A[N][M]);

int main() {
    int array_A[N][M];
    double array_B[N];

    fill_array_A(array_A); 
    print_array_A(array_A, "<<<-- Ваш масив A [5x4] -->>>");
    
    calculate_array_B(array_A, array_B);
    print_array_B(array_B, "<<<-- Обчислений масив B -->>>");
    
    sort_columns_shell(array_A);
    print_array_A(array_A, "<<<-- Відсортований масив A -->>>");

    return 0;
}

void fill_array_A(int A[N][M]) {
    printf("Необхідно ввести %d цілих значень (%d рядків по %d стовпці).\n", N * M, N, M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("Введіть елемент A[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &A[i][j]);
        }
    }
}

void print_array_A(int A[N][M], const char* title) {
    printf("\n%s\n", title);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%5d", A[i][j]);
        }
        printf("\n");
    }
}

void calculate_array_B(int A[N][M], double B[N]) {
    for (int i = 0; i < N; ++i) {
        double sum = 0.0;
        int count = 0;
        
        for (int j = 0; j < M; ++j) {
            if (A[i][j] < 0) {
                sum += A[i][j];
                count++;
            }
        }

        if (count > 0) {
            B[i] = sum / count;
        } else {
            B[i] = 0;
        }
    }
}

void print_array_B(double B[N], const char* title) {
    printf("\n%s\n", title);
    for (int i = 0; i < N; ++i) {
        printf("B[%d] = %f\n", i, B[i]);
    }
}

void sort_columns_shell(int A[N][M]) {
    for (int j = 0; j < M; ++j) {
        for (int gap = N / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < N; ++i) {
                int temp = A[i][j]; 
                int k;
                
                for (k = i; k >= gap && A[k - gap][j] < temp; k -= gap) {
                    A[k][j] = A[k - gap][j];
                }
                
                A[k][j] = temp;
            }
        }
    }
}