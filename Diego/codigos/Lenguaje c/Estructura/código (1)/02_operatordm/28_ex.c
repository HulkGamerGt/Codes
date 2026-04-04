
// Decision making 

#include <stdio.h>
 
int main () {

   /* local variable declaration */
   int a, b, c;
   
   /*use different values for a, b and c as
   10, 5, 7
   10, 20, 15
   */
   
   // change to 10,20,15 respectively next time
   a = 10; b = 5; c = 7;
   
   if (a>=b && a>=c){
      printf ("a is greater than b and c \n");
   }
   printf("a: %d b:%d c:%d", a, b, c);
 
   return 0;
}