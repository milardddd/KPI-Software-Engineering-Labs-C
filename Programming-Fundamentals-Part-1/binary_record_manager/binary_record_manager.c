#include <stdio.h>
#include <termios.h>
#include <unistd.h>

typedef struct{
    char name[40];
    float square;
    float population;
} record;

void printf_header(){
    printf("\n=============================\n");
    printf("Ця програмка працює з файлами\n");
    printf("=============================\n");
}

void printf_menu_text(){
    printf("\nМеню:\n\n");
    printf("Файли:                      Записи:\n");
    printf("0 - Створити файл           3 - Створити запис\n");
    printf("1 - Прочитати файл          4 - Прочитати запис\n");
    printf("2 - Видалити файл           5 - Відредагувати запис\n");
    printf("                            6 - Відсортувати запис\n");
    printf("                            7 - Вставити запис\n");
    printf("                            8 - Видалити запис\n");
    printf("            9 - Вийти з програми\n");
    printf("            10 - Перевірити заголовок файлу\n");
}

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

int ask_option(){
    int opt;
    printf("Оберіть опцію(з меню зверху):\n");
    if (scanf("%d", &opt) != 1) {
        while (getchar() != '\n');     
        return -1;
    }
    return opt;
}


int main(void){
    int key;
    int choice;
    char filename[50];
    char current_filename[100];
    int file_exist = 0;
    const int SIGNATURE = 1234567;

    do {
    printf_header();
    printf_menu_text();

    choice = ask_option();

      switch (choice) {
        case 0:
            printf("Введіть назву файлу: ");
            scanf("%s", filename);
            FILE *f = fopen(filename, "wb");
            if(f !=NULL){
                fwrite(&SIGNATURE, sizeof(int), 1, f);
                fclose(f);
                printf("Файл %s створено успішно!\n", filename);
                file_exist = 1;
            }
            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:
            printf("Вихід з програми...\n");
            break;
        case 10:

            break;
      default:
            if(choice != 9)
            printf("Невірний вибір!\n");
        break;
      }  

    } while (choice != 9);
    return 0;
}