
// Pointer and arrays 

#include <stdio.h>

int main(){

   int a = 5;
   int *b = &a;
   
   printf("Address of a: %d\n", b);
   b++;
   printf("After increment, Address of a: %d\n", b);
   
   return 0;
}