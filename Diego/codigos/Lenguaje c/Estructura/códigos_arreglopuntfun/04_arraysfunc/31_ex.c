
// array, variable length

#include <stdio.h>

int main(){

   int i, j;
   int size; // variable to hold size of one-dimensional array

   printf("Enter the size of one-dimensional array: ");
   scanf("%d", &size);

   int arr[size];
   
   for(i = 0; i < size; ++i){
      printf("Enter a number: ");
      scanf("%d", &j);
      arr[i] = j;
   }

   for(i = 0; i < size; ++i)
   printf("a[%d]: %d\n", i, arr[i]);

   return 0;
}