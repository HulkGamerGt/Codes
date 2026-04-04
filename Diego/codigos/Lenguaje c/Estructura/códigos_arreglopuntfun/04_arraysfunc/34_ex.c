
// array variable length

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void oneDArray(int length, int a[length]); 

// function prototype
void twoDArray(int row, int col, int a[row][col]);

// function prototype
int main(){

   int i, j; 
   
   // counter variable
   int size; 
   
   // variable to hold size of one dimensional array
   int row, col; 
   
   // number of rows & columns of two D array
   srand(time(NULL));
   
   printf("Enter the size of one-dimensional array: ");
   scanf("%d", &size);
   
   printf("Enter the number of rows & columns of 2-D array:\n");
   scanf("%d %d", &row, &col);

   // declaring arrays
   int arr[size];
   
   // 2-D array
   int arr2D[row][col]; 

   // one dimensional array
   for(i = 0; i < size; ++i){
      arr[i] = rand() % 100 + 1;
   }

   // two dimensional array
   for(i = 0; i < row; ++i){
      for(j = 0; j < col; ++j){
         arr2D[i][j] = rand() % 100 + 1;
      }
   }

   // printing arrays
   printf("One-dimensional array:\n");
   
   // oneDArray(size, arr);
   for(i = 0; i < size; ++i)
   printf("a[%d]: %d\n", i, arr[i]);
   printf("\nTwo-dimensional array:\n");
   
   // twoDArray(row1, col1, arr2D);
   for(i = 0; i < row; ++i){
      printf("\n");
      for (j = 0; j < col; ++j)
         printf("%5d", arr2D[i][j]);
   }
}