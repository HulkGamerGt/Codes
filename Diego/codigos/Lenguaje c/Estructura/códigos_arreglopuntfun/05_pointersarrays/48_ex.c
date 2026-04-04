
// pointer to array

#include <stdio.h>

int main(){

   /* an array with 5 elements */
   double balance[5] = {1000.0, 2.0, 3.4, 17.0, 50.0};
   double *ptr;
   int i;

   ptr = balance;
 
   /* output each array element's value */
   printf("Array values using pointer: \n");
	
   for(i = 0; i < 5; i++){
      printf("*(ptr + %d): %f\n",  i, *(ptr + i));
   }

   printf("\nArray values using balance as address:\n");
	
   for(i = 0; i < 5; i++){
      printf("*(balance + %d): %f\n",  i, *(balance + i));
   }
 
   return 0;
}