#include <stdio.h>
#include <string.h> 

#define N 10

void createArray1(int arr[], int n);
void createArray2(int arr[], int n);
void printArray(int arr[], int n, const char* title);

int findCommonElements(int arr1[], int arr2[], int n, int outArr[]);
int countLessThan(int arr[], int n, int value);

void bubbleSortAsc(int arr[], int n);
int linearSearch(int arr[], int n, int target);
int binarySearch(int arr[], int n, int target);

int main() {
    int array1[N];
    int array2[N];
    int array3[N];
    int target_number; 
    
    createArray1(array1, N);
    printArray(array1, N, "1-й масив (130 - i):");

    createArray2(array2, N);
    printArray(array2, N, "2-й масив (120 + i):");
    printf("\n");

    int k = findCommonElements(array1, array2, N, array3);
    
    printArray(array3, k, "3-й масив (спільні елементи):");
    if (k == 0) {
        printf("Спільних елементів не знайдено.\n");
        return 1; 
    }
    printf("\n");
 
    int count = countLessThan(array3, k, 127);
    printf("Кількість елементів, менших за 127: %d\n", count);
    printf("\n"); 

    printf("Введіть число для пошуку в 3-му масиві: ");
    scanf("%d", &target_number);
    printf("\n");

    int linear_pos = linearSearch(array3, k, target_number);
    if (linear_pos != -1) {
        printf("1. Лінійний пошук: Число %d знайдено. Позиція: %d\n", target_number, linear_pos);
    } else {
        printf("1. Лінійний пошук: Число %d не знайдено.\n", target_number);
    }

    bubbleSortAsc(array3, k);
    
    printf("\n");
    printArray(array3, k, "Масив відсортовано для бінарного пошуку:");
    printf("\n");

    int binary_pos = binarySearch(array3, k, target_number);
    if (binary_pos != -1) {
        printf("2. Бінарний пошук: Число %d знайдено. Позиція (у відсортованому масиві): %d\n", target_number, binary_pos);
    } else {
        printf("2. Бінарний пошук: Число %d не знайдено.\n", target_number);
    }
    
    return 0;
}

void createArray1(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = 130 - i;
    }
}

void createArray2(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = 120 + i;
    }
}

void printArray(int arr[], int n, const char* title) {
    printf("%s\n", title);
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

int findCommonElements(int arr1[], int arr2[], int n, int outArr[]) {
    int i, j;
    int k = 0;
    
    for (i = 0; i < n; i++) {
        int found = 0; 
        j = 0;
        
        while (j < n && found == 0) { 
            if (arr1[i] == arr2[j]) {
                outArr[k] = arr1[i];
                k++;
                found = 1; 
            }
            j++; 
        }
    }
    return k;
}

int countLessThan(int arr[], int n, int value) {
    int count = 0;
    for (int i = 0; i < n; i++) { 
        if (arr[i] < value) {
            count++;
        }
    }
    return count; 
}

void bubbleSortAsc(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i + 1; 
        }
    }
    return -1; 
}

int binarySearch(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; 

        if (arr[mid] == target) {
            return mid + 1; 
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }
    return -1; 
}