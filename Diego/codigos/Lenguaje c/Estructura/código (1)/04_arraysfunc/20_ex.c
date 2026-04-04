
// Multi dimensional array

#include <stdio.h>

int  main() {
   int arr[3][5] = {1,2,3,4,5, 10,20,30,40,50, 5,10,15,20,25};
   int i, j;

   for (i=0; i<3; i++){
      for (j=0; j<5; j++){
         printf("%4d", arr[i][j]);
      }
      printf("\n");
   }
   return 0;
}