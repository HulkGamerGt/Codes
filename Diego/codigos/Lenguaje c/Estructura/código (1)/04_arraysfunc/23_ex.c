
// Arrays

#include<stdio.h>
int main(){
   int mat1[3][3] = { {2, 4, 1} , {2, 3, 9} , {3, 1, 8} };
   int mat2[3][3] = { {1, 2, 3} , {3, 6, 1} , {2, 4, 7} };
   int mat3[3][3], sum=0, i, j, k;

   for(i=0; i<3; i++){
      for(j=0; j<3; j++){
         sum=0;
         for(k=0; k<3; k++)
            sum = sum + mat1[i][k] * mat2[k][j];
         mat3[i][j] = sum;
      }
   }
   printf("\nMatrix 1 ...\n");
   for(i=0; i<3; i++){
      for(j=0; j<3; j++)
         printf("%d\t", mat1[i][j]);
      printf("\n");
   }

   printf("\nMatrix 2 ...\n");
   for(i=0; i<3; i++){
      for(j=0; j<3; j++)
         printf("%d\t", mat2[i][j]);
      printf("\n");
   }

   printf("\nMultiplication of the two given Matrices: \n");
   for(i=0; i<3; i++){
      for(j=0; j<3; j++)
      printf("%d\t", mat3[i][j]);
      printf("\n");
   }

   return 0;
}