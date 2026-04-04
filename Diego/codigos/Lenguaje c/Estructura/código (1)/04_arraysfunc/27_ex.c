
// Multi domensional array, and function, 

#include <stdio.h>

int twoDarr(int *arr);

int main(){
   int arr[][3]= {10, 34, 21, 78, 5, 25};
   twoDarr(*arr);
   return 0;
}

int twoDarr(int *arr){
   int max=*arr;
   int i, j;
   for (i=0; i<2; i++){
      for (j=0; j<3; j++){
         printf("%d\t", arr[i]);
         arr++;
      }
      printf("\n");
   }

   return 0;
}