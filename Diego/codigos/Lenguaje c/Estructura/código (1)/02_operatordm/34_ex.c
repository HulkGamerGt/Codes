
// Nested deciwsion making

#include <stdio.h>
 
int main (){

   // local variable definition
   // check with different values 120, 250 and 74
   int a = 120;
   printf("value of a is : %d\n", a );

   // check the boolean condition
   if(a >= 100){
   
      // this will check if a is between 100-200
      if(a < 200){
         // if the condition is true, then print the following
         printf("Value of a is between 100 and 200\n" );
      }
      else{
          printf("Value of a is more than 200\n");
      }
   }
   else{ 
       // executed if a < 100
       printf("Value of a is less than 100\n");
   }

   return 0;
}