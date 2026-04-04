
// NULL Pointer

#include <stdio.h> 

int main(){ 

   int *ptr = NULL;   // null pointer

   if (ptr == NULL) { 
      printf("Pointer is a NULL pointer"); 
   } 
   else { 
      printf("Value stored in the address referred by the pointer: %d", *ptr); 
   } 
   
   return 0; 
}