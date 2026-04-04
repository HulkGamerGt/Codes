
// array, function,and memory allocation

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
float * arrfunction(int);
int main(){
   int x=16, i;
   float *arr = arrfunction(x);
   printf("Square of %d: %f\n", x, arr[0]);
   printf("cube of %d: %f\n", x, arr[1]);
   printf("Square root of %d: %f\n", x, arr[2]);
   return 0;
}
float *arrfunction(int x){
   float *arr = (float *)malloc(3*sizeof(float));
   arr[0]=pow(x,2);
   arr[1]=pow(x, 3);
   arr[2]=pow(x, 0.5);
   return arr;
}