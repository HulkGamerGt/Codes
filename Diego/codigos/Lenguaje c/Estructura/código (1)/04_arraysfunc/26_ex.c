
// Arrays, function call by reference

#include <stdio.h>
int max(int *arr, int length);
int main(){
   int arr[] = {10, 34, 21, 78, 5};
   int length = sizeof(arr)/sizeof(int);
   int maxnum = max(arr, length);
   printf("max: %d", maxnum);
}
int max(int *arr, int length){
   int max=*arr;
   int i;
   for (i=0; i<length; i++){   
      printf("arr[%d]: %d\n", i, (*arr));
      if ((*arr)>max)
         max = (*arr);
      arr++;
   }
   return max;
}