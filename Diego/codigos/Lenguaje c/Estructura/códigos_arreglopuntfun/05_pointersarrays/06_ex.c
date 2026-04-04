
#include <stdio.h>

int main(){

   int var = 100;
   int *intptr = &var;
   
   printf("Variable: %d \nAddress of Variable: %p \n\n", var, &var);
   printf("intptr: %p \nAddress of intptr: %p \n\n", intptr, &intptr);
   
   return 0;
}