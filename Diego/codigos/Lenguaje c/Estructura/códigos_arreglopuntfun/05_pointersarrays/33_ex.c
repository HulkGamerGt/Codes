
// Pointer of pointer

#include <stdio.h>

int main(){

   int a = 10;
   int *b = &a;
   printf("a: %d \nAddress of 'a': %d \nValue at a: %d\n\n", a, b, *b);

   int **c = &b;
   printf("b: %d \nPointer to 'b' is c: %d \nValue at b: %d\n", b, c, *c);
   printf("Value of 'a' from 'c': %d", **c);

   return 0;
}