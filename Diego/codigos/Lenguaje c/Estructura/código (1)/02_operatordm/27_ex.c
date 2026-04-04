
// Decision making

#include <stdio.h>
 
int main (){

   /* local variable declaration */
   int a;
   
   // run the program for different values of "a" 
   // Assign 12 first and 40 afterwards
   
   a = 12;  //change to 40 and run again
   printf("Value of a is : %d\n", a);
 
   // check the boolean condition using if statement
	
   if(a < 20){
      //if the condition is true, then print the following
      printf("a is less than 20\n" );
   }
   return 0;
}