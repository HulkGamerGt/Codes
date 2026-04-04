
// Call function by reference

#include <stdio.h>

/* Function definition to swap the values */
/* It receives the reference of two variables whose values are to be swapped */

int swap(int *x, int *y){

   int z;

   z = *x;   /* save the value at address x */
   *x = *y;  /* put y into x */
   *y = z;   /* put z into y */
  
   return 0;
}

/* The main() function has two variables "a" and "b" */ 
/* Their addresses are passed as arguments to the swap() function. */

int main(){

   /* local variable definition */
   int a = 10;
   int b = 20;
 
   printf("Before swap, value of a: %d\n", a );
   printf("Before swap, value of b: %d\n", b );
 
   /* calling a function to swap the values */
   swap(&a, &b);
 
   printf("After swap, value of a: %d\n", a);
   printf("After swap, value of b: %d\n", b);
 
   return 0;
}