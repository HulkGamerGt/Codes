
// Nested loops

#include <stdio.h>
 
int main(){

   int i, j;
	
   // outer loop
   for(i = 1; i <= 3; i++){
      
      // inner loop
      for(j = 1; j <= 3; j++){
         printf("i: %d j: %d\n", i, j);
      }
      printf("End of Inner Loop \n");
   }
   printf("End of Outer Loop");
 
   return 0;
}