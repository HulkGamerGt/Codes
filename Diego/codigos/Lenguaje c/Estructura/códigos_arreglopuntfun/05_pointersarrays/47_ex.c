
// Pointer to array

#include <stdio.h>

int main(){

   int *ptr;
   int balance[5] = {1, 2, 3, 4, 5};

   ptr = balance;

   printf("Pointer 'ptr' points to the address: %d", ptr);
   printf("\nAddress of the first element: %d", balance);
   printf("\nAddress of the first element: %d", &balance[0]);

   return 0;
}