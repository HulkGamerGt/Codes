
// Arryas, and function by reference

#include <stdio.h>
#include <math.h>
void arrfunction(int, float *);

int main(){
   int x=100;
   float arr[3];
   arrfunction(x, arr);
   printf("Square of %d: %f\n", x, arr[0]);
   printf("cube of %d: %f\n", x, arr[1]);
   printf("Square root of %d: %f\n", x, arr[2]);
   return 0;
}

void arrfunction(int x, float *arr){
   arr[0]=pow(x,2);
   arr[1]=pow(x, 3);
   arr[2]=pow(x, 0.5);
}