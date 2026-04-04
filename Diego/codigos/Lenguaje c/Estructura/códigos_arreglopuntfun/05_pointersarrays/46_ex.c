
#include <stdio.h>

float add(int a, int b){
   return a + b;
}

float subtract(int a, int b){
   return a - b;
}

float multiply(int a, int b){
   return a * b;
}

float divide(int a, int b){
   return a / b;
}

int main(){

   float (*ptr[])(int, int) = {add, subtract, multiply, divide};
   
   int a = 15, b = 10;
   
   // 1 for addition, 2 for subtraction 
   // 3 for multiplication, 4 for division
   int op = 3;
   
   if (op > 5) return 0;
   printf("Result: %.2f", (*ptr[op-1])(a, b));
   
   return 0;
}