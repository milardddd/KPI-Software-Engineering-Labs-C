/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #5
 * Topic: Pointers and Arrays. String Manipulation
 *
 * Author: Timofii Rybalko
 * Created: 11/2025
 *
 * Description:
 * Advanced string manipulation using pointers to pointers and wide strings
 * (Unicode). Implements case-insensitive sorting by swapping pointers to
 * dynamically allocated memory blocks.
 */

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>

void sort(wchar_t** mass, int num) {
  int i, j;
  wchar_t* tmp;

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

int get_integer_input(const char* prompt) {
  char buffer[20];
  printf("%s", prompt);
  fgets(buffer, sizeof(buffer), stdin);
  return atoi(buffer);
}

int main(void) {
  setlocale(LC_ALL, "");
  srand((unsigned int)time(NULL));

  wint_t key;

  printf("\n\033[1;36m==============================================\033[0m\n");
  printf("      \033[1mSTRING ARRAY SORTING (A-Z)\033[0m          \n");
  printf(" \033[3mThis program sorts strings alphabetically,\033[0m  \n");
  printf(" \033[3mignoring case (Apple == apple).\033[0m          \n");
  printf("\033[1;36m==============================================\033[0m\n");

  do {
    int nums, numc, choice;
    char choice_buffer[10];

    wchar_t** list = NULL;
    wchar_t** addr = NULL;
    int memory_allocated = 0;

    do {
      nums = get_integer_input("\nEnter the number of strings -> ");
      if (nums <= 0) {
        printf("Error: please enter a positive number (1, 2, 3...).\n");
      }
    } while (nums <= 0);

    do {
      numc = get_integer_input("Enter the number of characters per string -> ");
      if (numc <= 0) {
        printf("Error: please enter a positive number.\n");
      }
    } while (numc <= 0);

    list = malloc(nums * sizeof(wchar_t*));
    addr = malloc(nums * sizeof(wchar_t*));

    if (list == NULL || addr == NULL) {
      printf("Critical Error: Memory allocation failed!\n");
      return 0;
    }

    for (int i = 0; i < nums; i++) {
      list[i] = malloc((numc + 1) * sizeof(wchar_t));
      if (list[i] == NULL) {
        printf("Critical Error: Memory allocation for string failed!\n");
        return 0;
      }
    }
    memory_allocated = 1;

    int valid_choice = 0;
    do {
      printf("Choose filling method:\n");
      printf("  1 - Manual entry\n");
      printf("  2 - Random (Latin A-Z only)\n");
      printf("Your choice -> ");

      fgets(choice_buffer, sizeof(choice_buffer), stdin);
      choice = atoi(choice_buffer);

      switch (choice) {
        case 1:
          printf("Enter %d strings (max %d chars, extra will be discarded):\n",
                 nums, numc);
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
          printf("Generating %d strings with %d characters...\n", nums, numc);
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
          printf("Invalid choice. Please try again.\n");
      }
    } while (valid_choice == 0);

    for (int i = 0; i < nums; i++) {
      addr[i] = list[i];
    }

    printf("\n--- Strings before sorting ---\n");
    for (int i = 0; i < nums; i++) {
      wprintf(L"%d-> %ls\n", i + 1, list[i]);
    }

    sort(addr, nums);

    printf("\n--- Strings after sorting ---\n");
    for (int i = 0; i < nums; i++) {
      wprintf(L"%d-> %ls\n", i + 1, addr[i]);
    }

    if (memory_allocated) {
      printf("\n...Freeing memory...\n");
      for (int i = 0; i < nums; i++) {
        free(list[i]);
      }
      free(list);
      free(addr);
    }

    printf("\nPress Enter to repeat or Q+Enter to exit...\n");
    key = getwchar();
    if (key != L'\n') {
      wint_t c;
      while ((c = getwchar()) != L'\n' && c != WEOF);
    }
  } while (key == L'\n');

  return 0;
}