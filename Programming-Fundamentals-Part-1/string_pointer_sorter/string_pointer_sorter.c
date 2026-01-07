#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

void sort(wchar_t **mass, int num) {
    int i, j;
    wchar_t *tmp;

    for (i = 0; i < num - 1; i++) {
        for (j = i + 1; j < num; j++) {
            if (wcscasecmp(mass[i], mass[j]) > 0) { 
                tmp = mass[i];
                mass[i] = mass[j];
                mass[j] = tmp;
            }
        }
    }
}

int my_random(int range_min, int range_max) {
    return (range_min + rand() % (range_max - range_min + 1));
}

int get_integer_input(const char *prompt) {
    char buffer[20]; 
    printf("%s", prompt);
    fgets(buffer, sizeof(buffer), stdin);
    return atoi(buffer);
}

int main(void) {
    setlocale(LC_ALL, ""); 

    wint_t key;
    
    srand((unsigned int)time(NULL)); 

        printf("\n\033[1;36m==============================================\033[0m\n");
        printf("      \033[1mСОРТУВАННЯ МАСИВУ РЯДКІВ (A-Z)\033[0m          \n");
        printf(" \033[3mЦя програма впорядковує рядки за алфавітом,\033[0m  \n");
        printf(" \033[3mігноруючи регістр (Apple == apple).\033[0m          \n");
        printf("\033[1;36m==============================================\033[0m\n");

    do {
        int nums, numc, choice;
        char choice_buffer[10];

        wchar_t **list = NULL;
        wchar_t **addr = NULL;
        
        int memory_allocated = 0; 

        do {
            nums = get_integer_input("\nВведіть кількість рядків -> ");
            if (nums <= 0) {
                printf("Помилка: введіть додатне число (наприклад, 1, 2, 3...).\n");
            }
        } while (nums <= 0);

        do {
            numc = get_integer_input("Введіть кількість символів в рядку -> ");
            if (numc <= 0) {
                printf("Помилка: введіть додатне число (наприклад, 1, 2, 3...).\n");
            }
        } while (numc <= 0);
            
        list = malloc(nums * sizeof(wchar_t *));
        addr = malloc(nums * sizeof(wchar_t *));

        if (list == NULL || addr == NULL) {
            printf("Критична помилка виділення пам'яті!\n");
            return 0;
        }

        for (int i = 0; i < nums; i++) {
            list[i] = malloc((numc + 1) * sizeof(wchar_t)); 
            if (list[i] == NULL) {
                printf("Критична помилка виділення пам'яті для рядка!\n");
                return 0;
            }
        }
        memory_allocated = 1;

        int valid_choice = 0;
        do {
            printf("Оберіть спосіб заповнення:\n");
            printf("  1 - Вручну\n");
            printf("  2 - Рандомно (лише латиниця A-Z)\n");
            printf("Ваш вибір -> ");
            
            fgets(choice_buffer, sizeof(choice_buffer), stdin);
            choice = atoi(choice_buffer);

            switch (choice) {
                case 1:
                    printf("Введіть %d рядків (макс %d символів, зайві буде відкинуто):\n", nums, numc);
                    for (int i = 0; i < nums; i++) {
                        wprintf(L"%d >> ", i + 1);
                        
                        fgetws(list[i], numc + 1, stdin);
                        
                        if (wcschr(list[i], L'\n') == NULL) { 
                            wint_t c;
                            while ((c = getwchar()) != L'\n' && c != WEOF); 
                        }
                        
                        list[i][wcscspn(list[i], L"\n")] = 0; 
                    }
                    valid_choice = 1;
                    break;
                
                case 2:
                    printf("Генеруємо %d рядків по %d символів...\n", nums, numc);
                    for (int i = 0; i < nums; i++) {
                        for (int b = 0; b < numc; b++) {
                            char ch;
                            do {
                                ch = my_random(65, 122); 
                            } while (!((ch > 64 && ch < 91) || (ch > 96 && ch < 123)));
                            list[i][b] = (wchar_t)ch; 
                        }
                        list[i][numc] = L'\0';
                    }
                    valid_choice = 1;
                    break;

                default:
                    printf("Невірний вибір. Спробуйте ще раз.\n");
            }
        } while (valid_choice == 0);

        for (int i = 0; i < nums; i++) {
            addr[i] = list[i];
        }

        printf("\n--- Рядки до сортування ---\n");
        for (int i = 0; i < nums; i++) {
            wprintf(L"%d-> %ls\n", i + 1, list[i]); 
        }

        sort(addr, nums);

        printf("\n--- Рядки після сортування ---\n");
        for (int i = 0; i < nums; i++) {
            wprintf(L"%d-> %ls\n", i + 1, addr[i]);
        }
        
        if (memory_allocated) {
            printf("\n...Звільнення пам'яті...\n");
            for (int i = 0; i < nums; i++) {
                free(list[i]); 
            }
            free(list); 
            free(addr); 
        }

        printf("\nНатисніть Enter для повтору або Q+Enter для виходу...\n");
        key = getwchar();
        if (key != L'\n') {
            wint_t c;
            while ((c = getwchar()) != L'\n' && c != WEOF);
        }
    } while (key == L'\n');

    return 0;
}