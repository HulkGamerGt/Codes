
// Arrays

#include<stdio.h>
int main() {
   int num[10] = {50, 55, 67, 73, 45, 21, 39, 70, 49, 51};
   int size = sizeof(num) / sizeof(int);
   printf("element at lower bound num[0]: %d \n", num[0]);
   printf("at upper bound: %d byte \n", num[size-1]); 
   printf("length of int array: %ld \n", sizeof(num));
   double nm[10] = {50, 55, 67, 73, 45, 21, 39, 70, 49, 51};
   size = sizeof(nm) / sizeof(double);
   printf("element at lower bound nm[0]: %f \n", nm[0]);
   printf("element at upper bound: %f \n", nm[size-1]);
   printf("byte length of double array: %ld \n", sizeof(nm));

   return 0;
}