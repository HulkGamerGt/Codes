
// Nested decision makinf

#include <stdio.h>

int main(){
   int a = 15;
   printf("a: %d\n", a);

   if (a % 2 == 0) {
      if (a % 3 == 0){
         printf("Divisible by 2 and 3");
      }
      else {
         printf("Divisible by 2 but not 3");
      }
   }
   else {
      if (a % 3 == 0){
         printf("Divisible by 3 but not 2");
      }
      else{
         printf("Not divisible by 2, not divisible by 3");
      }
   }

   return 0;
}