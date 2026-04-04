
// Arrays of pointer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaring a structure
typedef struct {
  char title[50];
  float price;
} Book;

const int MAX = 3;
int main() {
  Book *book[MAX];

  // Initialize each book (pointer)
  for (int i = 0; i < MAX; i++) {
    book[i] = malloc(sizeof(Book));
    snprintf(book[i]->title, 50, "Book %d", i + 1);
    book[i]->price = 100 + i;
  }

  // Print details of each book
  for (int i = 0; i < MAX; i++) {
    printf("Title: %s, Price: %.2f\n", book[i]->title, book[i]->price);
  }

  // Free allocated memory
  for (int i = 0; i < MAX; i++) {
    free(book[i]);
  }

  return 0;
}