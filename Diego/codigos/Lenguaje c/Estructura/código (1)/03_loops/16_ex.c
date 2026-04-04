
// Nested loop 

#include <stdio.h>
 
int main(){

   int i, j;
   printf("Program to Print the Tables of 1 to 10 \n");
   
   // outer loop
   for(i = 1; i <= 10; i++){
      
      // inner loop
      for(j = 1; j <= 10; j++){
         printf("%4d", i*j);
      }
      printf("\n");
   }
   return 0;
}