
// Caal function by value and reference

#include <stdio.h>
#include <math.h>

/* function declaration */
int calculate(int, int *, int *);

int main(){

   int a = 10;
   int b, c;

   calculate(a, &b, &c);

   printf("a: %d \nSquare of a: %d \nCube of a: %d", a, b, c);
}

int calculate(int x, int *y, int *z){

   *y  = pow(x,2);
   *z = pow(x, 3);

   return 0;
}