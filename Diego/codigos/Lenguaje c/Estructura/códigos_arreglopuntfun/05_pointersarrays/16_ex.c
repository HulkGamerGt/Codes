
// Applications of pointers

#include <stdio.h>

int main(){

   int arr[] = {1,2,3,4,5};
   int *ptr = arr;

   for(int i = 0; i <= 4; i++){
      printf("arr[%d]: %d\n", i, *ptr);
      ptr++;
   }
   
   return 0;
}