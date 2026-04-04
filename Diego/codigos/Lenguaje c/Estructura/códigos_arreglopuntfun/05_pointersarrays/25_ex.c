
//  Pointer arithmetics

#include <stdio.h>

int main(){

   int a[]= {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
   int *x = &a[0]; // zeroth element
   int *y = &a[9]; // last element

   printf("Add of a[0]: %ld add of a[9]: %ld\n", x, y);
   printf("Subtraction of two pointers: %ld", y-x);

}