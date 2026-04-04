
// break stament in loop

#include <stdio.h>

/*break in while loop*/
int main () {

   int i = 2;
   int x = 121;
   printf("x: %d\n", x);
   
   while (i < x/2){
      if (x % i == 0)
         break;
      i++;
   }
   if (i >= x/2)
      printf("%d is prime", x);
   else
      printf("%d is not prime", x);

   return 0;
}