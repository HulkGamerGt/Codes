
// Return pointer from function

#include <stdio.h>
#include <math.h>

float * arrfunction(int);

int main(){

   int x = 100, i;
   float *arr = arrfunction(x);

   printf("Square of %d: %f\n", x, *arr);
   printf("Cube of %d: %f\n", x, arr[1]);
   printf("Square root of %d: %f\n", x, arr[2]);

   return 0;
}

float *arrfunction(int x){
   static float arr[3];
   arr[0] = pow(x,2);
   arr[1] = pow(x, 3);
   arr[2] = pow(x, 0.5);

   return arr;
}



