
// cahin of pointer

#include <stdio.h>

int main(){

   int a = 10;

   int *x = &a;
   int **y = &x;
   int ***z = &y;

   printf("a: %d\n", a);

   printf("a: %d\n", *x);   // dereferencing x;
   printf("a: %d\n", **y);  // double dereferencing y;
   printf("a: %d\n", ***z); // triple dereferencing z;

   return 0;
}
