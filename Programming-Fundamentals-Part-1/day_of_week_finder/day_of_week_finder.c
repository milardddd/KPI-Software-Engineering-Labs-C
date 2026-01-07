#include <stdio.h>

int main(void){
    #define minYear 1900
    #define maxYear 2099

    char key;

    do {
        int day, month, year;
        int n;
        int isLeap;
        int day_of_week;
        char buffer[100];
        char extra;
        int valid_input = 0;

        printf("Ця програма яка за датою виводить день тижня по Григоріанському календарю\n");

        do {
            printf("Введіть день: ");
            if (!fgets(buffer, sizeof(buffer), stdin)) continue;

            if (sscanf(buffer, " %d %c", &day, &extra) == 1) {
                if (day >= 1 && day <= 31) {
                    valid_input = 1;
                } else {
                    printf("Помилка! День повинен бути від 1 до 31\n");
                }
            } else {
                printf("Помилка! Введіть число\n");
            }
        } while (!valid_input);

        valid_input = 0;
        do {
            printf("Введіть місяць: ");
            if (!fgets(buffer, sizeof(buffer), stdin)) continue;

            if (sscanf(buffer, "%d %c", &month, &extra) == 1) {
                if (month >= 1 && month <= 12) {
                    valid_input = 1;
                } else {
                    printf("Помилка! Місяць повинен бути від 1 до 12\n");
                }
            } else {
                printf("Помилка! Введіть число\n");
            }
        } while (!valid_input);

        valid_input = 0;
        do {
            printf("Введіть рік від %d до %d: ", minYear, maxYear);
            if (!fgets(buffer, sizeof(buffer), stdin)) continue;

            if (sscanf(buffer, "%d %c", &year, &extra) == 1) {
                if (year >= minYear && year <= maxYear) {
                    valid_input = 1;
                } else {
                    printf("Помилка! Рік повинен бути від %d до %d\n", minYear, maxYear);
                }
            } else {
                printf("Помилка! Введіть число\n");
            }
        } while (!valid_input);


        isLeap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));

        if (month > 2)
            n = 0;
        else if (isLeap)
            n = 1;
        else 
            n = 2 ;
            
        day_of_week = ((int) (365.25 * year) + (int) (30.56 * month) + day + n) % 7;

        switch (day_of_week){
            case 0: printf("Понеділок\n"); break;
            case 1: printf("Вівторок\n"); break;
            case 2: printf("Середа\n"); break;
            case 3: printf("Четвер\n"); break;
            case 4: printf("П'ятниця\n"); break;
            case 5: printf("Субота\n"); break;
            case 6: printf("Неділя\n"); break;
        }

        printf("\nНатисніть Enter для повтору або Q+Enter для виходу...\n");

        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        key = buffer[0];

    }while (key == 10 );

    return 0;
}