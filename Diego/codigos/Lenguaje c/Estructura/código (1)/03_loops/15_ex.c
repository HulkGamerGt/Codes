
// Nested loop

#include <stdio.h>
 
int main(){

   int i, j;
	
   // outer for loop
   for (i = 1; i <= 3; i++){
   
      // inner while loop
      j = 1;
      while (j <= 3){
         printf("i: %d j: %d\n", i, j);
         j++;
      }
      printf("End of Inner While Loop \n");
   }
   printf("End of Outer For loop");
 
   return 0;
}