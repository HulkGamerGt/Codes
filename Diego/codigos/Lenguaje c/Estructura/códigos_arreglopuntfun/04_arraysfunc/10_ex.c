
// recursion

#include <stdio.h>

int bSearch(int array[], int start, int end, int element){
   
   if (end >= start){
      
      int mid = start + (end - start ) / 2;
      
      if (array[mid] == element)
         return mid;
      
      if (array[mid] > element)
         return bSearch(array, start, mid-1, element);
         return bSearch(array, mid+1, end, element);
   }
   return -1;
}

int main(void){
   int array[] = {5, 12, 23, 45, 	49, 67, 71, 77, 82};
   int n = 9;
   int element = 67;
   int index = bSearch(array, 0, n-1, element);
   
   if(index == -1 ){
      printf("Element not found in the array ");
   }
   else{
      printf("Element found at index: %d", index);
   }
   return 0;
}