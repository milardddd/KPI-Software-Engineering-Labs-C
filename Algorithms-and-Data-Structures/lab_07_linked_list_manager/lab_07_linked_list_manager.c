/**
 * KPI FIOT | Software Engineering
 * Algorithms and Data Structures
 * Laboratory Work #7
 * Topic: Linear Data Structures (Singly Linked Lists)
 *
 * Author: Timofii Rybalko
 * Created: 11/2025
 *
 * Description:
 * Implementation of a Singly Linked List for character data storage.
 * Features: Dynamic memory allocation, element deletion, and data filtering.
 * Variant 20: Filter elements based on ASCII threshold (char > '?').
 */

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  char data;
  struct Node* next;
};

void push(struct Node** head_ref, char new_data);
void delete_elements(struct Node** head_ref, int m);
void filter_variant_20(struct Node* src, struct Node** dest_ref);
void print_list(struct Node* node);

int main() {
  setlocale(LC_ALL, "");

  struct Node* list1 = NULL;
  struct Node* list2 = NULL;
  int N, M, i;
  char temp;

  printf("Введіть кількість елементів N (0-15): ");
  scanf("%d", &N);

  while ((getchar()) != '\n');

  printf("Введіть %d символів (натискайте Enter після кожного):\n", N);
  for (i = 0; i < N; i++) {
    printf("Символ %d: ", i + 1);
    scanf("%c", &temp);
    while ((getchar()) != '\n');
    push(&list1, temp);
  }

  printf("\nПочатковий список:\n");
  print_list(list1);

  printf("\nВведіть кількість елементів для видалення M (0-15): ");
  scanf("%d", &M);
  delete_elements(&list1, M);

  printf("Список після видалення:\n");
  print_list(list1);

  filter_variant_20(list1, &list2);

  printf("\nНовий список (елементи > '?'):\n");
  print_list(list2);

  return 0;
}

void push(struct Node** head_ref, char new_data) {
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = new_data;
  new_node->next = (*head_ref);
  (*head_ref) = new_node;
}

void delete_elements(struct Node** head_ref, int m) {
  int i;
  for (i = 0; i < m; i++) {
    if (*head_ref == NULL) {
      printf("Список порожній, неможливо видалити більше елементів.\n");
      return;
    }
    struct Node* temp = *head_ref;
    *head_ref = (*head_ref)->next;
    free(temp);
  }
}

void filter_variant_20(struct Node* src, struct Node** dest_ref) {
  struct Node* current = src;
  char threshold = '?';

  while (current != NULL) {
    if (current->data > threshold) {
      push(dest_ref, current->data);
    }
    current = current->next;
  }
}

void print_list(struct Node* node) {
  if (node == NULL) {
    printf(" (пусто)\n");
    return;
  }
  while (node != NULL) {
    printf(" %c ->", node->data);
    node = node->next;
  }
  printf(" NULL\n");
}