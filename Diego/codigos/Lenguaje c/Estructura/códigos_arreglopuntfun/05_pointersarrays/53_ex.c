
// chain of pointer

#include <stdio.h>

int main(){

   float a = 10.25;;

   float *x = &a;
   float **y = &x;
   float ***z = &y;

   printf("a: %f\n", a);

   // update with first pointer
   *x = 11.25;
   printf("a: %f\n", *x);

   // update with second pointer
   **y = 12.25;
   printf("a: %f\n", **y);

   // update with third pointer
   ***z = 13.25;
   printf("a: %f\n", ***z);

   return 0;
}