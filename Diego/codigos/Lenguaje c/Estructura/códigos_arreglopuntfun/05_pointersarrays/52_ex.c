
// chain of pinter

#include <stdio.h>

int main(){

   float a = 10.25;

   float *x = &a;
   float **y = &x;
   float ***z = &y;

   printf("a: %f\n", a);
   printf("a: %f\n", *x);
   printf("a: %f\n", **y);
   printf("a: %f\n", ***z);

   return 0;
}