
// Arrays and function

#include <stdio.h>
float average(int arr[], int length);
int main(){
   int arr[] = {10, 34, 21, 78, 5};
   int length = sizeof(arr)/sizeof(int);
   float avg = average(arr, length);
   printf("average: %f", avg);
}
float average(int arr[], int length){
   int sum=0;
   int i;
   for (i=0; i<length; i++){
      printf("arr[%d]: %d\n", i, arr[i]);
      sum+=arr[i];
   }
   return (float)sum/length;
}