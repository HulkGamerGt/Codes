
// recursion

#include <stdio.h>
#include <math.h>

/* function declaration */
int factorial(int i){

   if(i <= 1){
      return 1;
   }
   return i * factorial(i - 1);
}
int main(){
   int a = 5;
   int f = factorial(a);
   
   printf("a: %d \n", a);
   printf("Factorial of a: %d", f);
   return 0;
}