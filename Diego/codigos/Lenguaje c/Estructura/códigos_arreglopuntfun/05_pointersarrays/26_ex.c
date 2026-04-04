
// Pointers arithmetics

#include <stdio.h>

const int MAX = 3;

int main() {
  int var[] = {10, 100, 200};
  int i, *ptr1, *ptr2;

  // Initializing pointers
  ptr1 = var;
  ptr2 = &var[MAX - 1];

  while (ptr1 <= ptr2) {
    printf("Address of var[%d] = %p\n", i, ptr1);
    printf("Value of var[%d] = %d\n", i, *ptr1);

    /* point to the previous location */
    ptr1++;
    i++;
  }

  return 0;
}