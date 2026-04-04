
// Multi dimensional array, variable length

#include <stdio.h>

int main(){

   int i, j, x;
   
   int row, col; // number of rows & columns of two D array

   printf("Enter number of rows & columns of 2-D array:\n");
   scanf("%d %d", &row, &col);

   int arr2D[row][col];
   for(i = 0; i < row; ++i){
      for(j = 0; j < col; ++j){
         printf("Enter a number: ");
         scanf("%d", &x);
         arr2D[i][j] = x;
      }
   }

   for(i = 0; i < row; ++i){
      printf("\n");
      for(j = 0; j < col; ++j)
         printf("%d\t", arr2D[i][j]);
   }

   return 0;
}