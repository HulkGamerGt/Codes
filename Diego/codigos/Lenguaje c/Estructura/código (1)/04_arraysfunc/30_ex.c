
// Array, function, struct

#include <stdio.h>
#include <math.h>

struct mystruct{
   float arr[3];
};
struct mystruct myfunction(int x);

int main(){
   int x = 9;
   struct mystruct s = myfunction(x);
   printf("Square of %d: %f\n", x, s.arr[0]);
   printf("cube of %d: %f\n", x, s.arr[1]);
   printf("Square root of %d: %f\n", x, s.arr[2]);
   return 0;
}

struct mystruct myfunction(int x){
   struct mystruct s1;
   s1.arr[0]=pow(x,2);
   s1.arr[1]=pow(x,3);
   s1.arr[2]=pow(x, 0.5);
   return s1;
}