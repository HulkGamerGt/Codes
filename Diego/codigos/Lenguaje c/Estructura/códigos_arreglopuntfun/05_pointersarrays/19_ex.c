
// Aplications of pointer

#include <stdio.h>

// Creating a function to find
// addition and subtraction
// of two numbers
void funAddSub(int a, int b, int* add, int* sub) {
  *add = a + b;
  *sub = a - b;
}

int main() {
  int num1 = 10;
  int num2 = 3;

  // Variables to store results
  int res1, res2;

  // Calling function to get add and sub
  // by passing the address of res1 and res2
  funAddSub(num1, num2, &res1, &res2);

  // Printing the result
  printf("Addition is %d and subtraction is %d", res1, res2);

  return 0;
}