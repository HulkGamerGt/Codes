
// arrays

// Initialization of an integer array
#include <stdio.h>

int main() 
{
  int numbers[5] = {10, 20, 30, 40, 50};

  int i;  // loop counter

  // Printing array elements
  printf("The array elements are : ");
  for (i = 0; i < 5; i++) {
    printf("%d ", numbers[i]);
  }

  return 0;
}
