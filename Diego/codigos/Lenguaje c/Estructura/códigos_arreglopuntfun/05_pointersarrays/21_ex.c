
// Pointer arithmetics

#include <stdio.h>

int main(){

   double x = 10;
   double *y = &x;
   
   printf("value of y before decrement: %ld\n", y);
   
   y--;
   
   printf("value of y after decrement: %ld", y);
}