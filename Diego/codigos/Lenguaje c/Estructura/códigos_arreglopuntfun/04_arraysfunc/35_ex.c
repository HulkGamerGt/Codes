
// jagged array

#include <stdio.h>

int main(){

   int a[] = {1,2};
   int b[] = {3,4,5};
   int c[] = {6,7,8,9};
   
   int l1 = sizeof(a)/sizeof(int), 
   l2 = sizeof(b)/sizeof(int), 
   l3 = sizeof(c)/sizeof(int);
   
   int *arr[] = {a,b,c};
   int size[] = {l1, l2, l3};
   int *ptr;
   int i, j, k = 0;

   for(i = 0; i < 3; i++){
      ptr = arr[i];
      for(j = 0; j < size[k]; j++){
         printf("%d\t", *ptr);
         ptr++;
      }
      printf("\n");
      k++;
      arr[i]++;
   }
   
   return 0;
}