
// Continue statement in loop

#include <stdio.h>

int main(){
   int i = 0;

   while (i < 10){
      i++;
      if(i%2 == 0)
         continue;

      printf("i: %d\n", i);

   }
}