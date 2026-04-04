
// Increment and decrement operators

#include <stdio.h>

int main() {
  int a = 5, b = 5, c = 5, d = 5;
  
  a++; // postfix increment
  ++b; // prefix increment
  c--; // postfix decrement
  --d; // prefix decrement

  printf("a = %d\n", a);
  printf("b = %d\n", b);
  printf("c = %d\n", c);
  printf("d = %d\n", d);

  return 0;
}