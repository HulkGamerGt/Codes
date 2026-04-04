
// pointer of pointers

#include <stdio.h>

int main() {
  // An integer variable
  int a = 100;

  // Pointer to integer
  int *ptr = &a;

  // Pointer to pointer (double pointer)
  int **dptr = &ptr;

  printf("Value of 'a' is : %d\n", a);
  printf("Value of 'a' using pointer (ptr) is : %d\n", *ptr);
  printf("Value of 'a' using double pointer (dptr) is : %d\n", **dptr);

  return 0;
}