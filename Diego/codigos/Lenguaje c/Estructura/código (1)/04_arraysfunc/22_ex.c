
// Arryas

#include <stdio.h>

int  main() {
   int arr[3][5] = {{1,2,3,4,5}, {10,20,30,40,50}, {5,10,15,20,25}};
   int i, j;
   int sum;

   for (i=0; i<3; i++){
      sum=0;
      for (j=0; j<5; j++){
         sum+=arr[i][j];
      }
      printf("Sum of row %d: %d\n", i, sum);
   }
   return 0;
}