/**
 * KPI FIOT | Software Engineering
 * Laboratory Work #9
 * Topic: File Operations and Binary Data Management
 *
 * Author: Timofii Rybalko
 * Created: 01/2026
 *
 * Description:
 * A file management utility for handling binary records of geographic data.
 * Implements file creation with a unique signature for integrity verification,
 * and provides a menu-driven interface for CRUD operations on binary data.
 */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Structure for storing geographic records
typedef struct {
  char name[40];
  float square;
  float population;
} record;

void printf_header() {
  printf("\n=========================================\n");
  printf("      FILE MANAGEMENT UTILITY (v1.0)\n");
  printf("=========================================\n");
}

void printf_menu_text() {
  printf("\nMenu:\n\n");
  printf("File Operations:             Record Operations:\n");
  printf("0 - Create new file          3 - Add new record\n");
  printf("1 - Read file content        4 - Display record\n");
  printf("2 - Delete file              5 - Edit record\n");
  printf("                             6 - Sort records\n");
  printf("                             7 - Insert record\n");
  printf("                             8 - Delete record\n");
  printf("            9 - Exit Program\n");
  printf("            10 - Verify File Signature\n");
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

int ask_option() {
  int opt;
  printf("\nSelect an option from the menu: ");
  if (scanf("%d", &opt) != 1) {
    while (getchar() != '\n');
    return -1;
  }
  return opt;
}

int main(void) {
  int choice;
  char filename[50];
  const int SIGNATURE = 1234567;

  do {
    printf_header();
    printf_menu_text();

    choice = ask_option();

    switch (choice) {
      case 0:
        printf("Enter filename to create: ");
        scanf("%s", filename);
        FILE* f = fopen(filename, "wb");
        if (f != NULL) {
          fwrite(&SIGNATURE, sizeof(int), 1, f);
          fclose(f);
          printf("Success: File '%s' created successfully!\n", filename);
        } else {
          printf("Error: Could not create file.\n");
        }
        break;

      case 1:
        printf("Feature 'Read File' is under development...\n");
        break;

      case 2:
        printf("Feature 'Delete File' is under development...\n");
        break;

      case 3:
        printf("Feature 'Add Record' is under development...\n");
        break;

      case 9:
        printf("Exiting program...\n");
        break;

      case 10:
        printf("Feature 'Verify Signature' is under development...\n");
        break;

      default:
        if (choice != 9) printf("Invalid selection! Please try again.\n");
        break;
    }

  } while (choice != 9);

  return 0;
}