
// Loop

#include <stdio.h>

int main(){
   int a;

   // for loop execution
   for(a = 1; ; a++){
      printf("a: %d\n", a);
      if(a == 5)
      break;
   }
   return 0;
}