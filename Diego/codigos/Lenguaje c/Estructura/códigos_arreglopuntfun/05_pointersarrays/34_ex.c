
// pointer to function

#include <stdio.h>

/* function declaration */
int add(int *, int *);

int main(){

   int a = 10, b = 20;
   int c = add(&a, &b);
   printf("Addition: %d", c);
}

int add(int *x, int *y){
   int z = *x + *y;
   
   return z;
}