
// Arrays and functions

#include <stdio.h>
float average(int arr[5]);
int main(){
   int arr[] = {10, 34, 21, 78, 5};
   float avg = average(arr);
   printf("average: %f", avg);
}
float average(int arr[5]){
   int sum=0;
   int i;
   for (i=0; i<5; i++){
      printf("arr[%d]: %d\n", i, arr[i]);
      sum+=arr[i];
   }
   return (float)sum/5;
}