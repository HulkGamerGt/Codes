
// Integer and float inputs

#include <stdio.h>

int main(){

   int num1;
   float num2;
   
   printf("Enter two numbers: ");
   scanf("%d %f", &num1, &num2);
   
   printf("You entered an integer: %d a floating-point number: %6.2f", num1, num2);
   
   return 0;
}