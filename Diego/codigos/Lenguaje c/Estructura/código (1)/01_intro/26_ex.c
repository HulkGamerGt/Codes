
// Booleans

#include <stdio.h>
#include <stdbool.h>

int main(){
  
   bool x;
   x = 10 > 5;
  
   if(x)
      printf("x is True\n");  
   else
      printf("x is False\n");
    
   bool y;
   int marks = 40;
   y = marks > 50;
  
   if(y)
      printf("Result: Pass\n");  
   else
      printf("Result: Fail\n");  
}