
// NULL pointer

#include <stdio.h>
#include <stdlib.h>

int main(){

   int* ptr = (int*)malloc(sizeof(int));


   if (ptr == NULL){
      printf("Memory Allocation Failed");
      exit(0);
   }
   else{
      printf("Memory Allocated successfully");
   }

   return 0;
}