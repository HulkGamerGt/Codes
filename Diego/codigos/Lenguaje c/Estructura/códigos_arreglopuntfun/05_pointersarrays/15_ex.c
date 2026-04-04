
// Pointer and array 

#include <stdio.h>

int main(){

   int arr[5] = {1, 2, 3, 4, 5};
   int *b = arr;
   int i;

   for(i = 0; i <= 4; i++){
      printf("a[%d] = %d\n",i,  *(b+i));
   }
   
   return 0;
}