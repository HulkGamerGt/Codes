
// Pointer of Pointer

#include <stdio.h>

int main(){

   int a = 10;
   int *b = &a;
   printf("a: %d \nPointer to 'a' is 'b': %d \nValue at 'b': %d", a, b, *b);

   return 0;
}