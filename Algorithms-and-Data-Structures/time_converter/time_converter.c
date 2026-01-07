#include <stdio.h>

int main() {
    int minutes, hours, mins;
    printf("Введіть кількість хвилин: ");
    scanf("%d", &minutes);
    hours = minutes / 60;
    mins = minutes % 60;
    printf("%d хвилин = %d год %d хв\n", minutes, hours, mins);     
    return 0;
}