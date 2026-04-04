
// function

#include <stdio.h>

/* function returning the max between two numbers */
int max(int num1, int num2){

   /* local variable declaration */
   int result;
   
   if(num1 > num2)
      result = num1;
   else
      result = num2;
 
   return result; 
}

int main(){
   printf("Comparing two numbers using max() function: \n");
   printf("Which of the two, 75 or 57, is greater than the other? \n");
   printf("The answer is: %d", max(75, 57));
    
   return 0;
}