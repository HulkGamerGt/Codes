
// Logical operator

#include <stdio.h>

int main(){

   char a = 'a';
   char b = '\0'; // Null character

   if (a && b){
      printf("Line 1 - Condition is true\n" );
   }

   if (a || b){
      printf("Line 2 - Condition is true\n" );
   }
   
   return 0;
}
