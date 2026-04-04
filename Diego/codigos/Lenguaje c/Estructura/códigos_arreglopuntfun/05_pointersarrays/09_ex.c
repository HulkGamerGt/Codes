
// Pointer

#include <stdio.h>

int main(){

   int var = 10;
   int *intptr = &var;
   int **ptrptr = &intptr;
   
   printf("var: %d \nAddress of var: %d \n\n",var, &var);
   printf("inttptr: %d \nAddress of inttptr: %d \n\n", intptr, &intptr);
   printf("var: %d \nValue at intptr: %d \n\n", var, *intptr);
   printf("ptrptr: %d \nAddress of ptrtptr: %d \n\n", ptrptr, &ptrptr);
   printf("intptr: %d \nValue at ptrptr: %d \n\n", intptr, *ptrptr);
   printf("var: %d \n*intptr: %d \n**ptrptr: %d", var, *intptr, **ptrptr);
   
   return 0;
}