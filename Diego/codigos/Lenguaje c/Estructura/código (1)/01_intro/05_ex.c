
// Comments, one line

/* Online C Compiler and Editor */
#include <stdio.h>
#include <math.h>

/*forward declaration of function*/
float area_of_square(float);

float area_of_square(float side){
   float area = pow(side,2);
   return area;
}

// main function - entire line is a comment
int main(){

   // variable declaration (this comment is after the C statement)
   float side = 5.50; 
     
   float area = area_of_square(side);   // calling a function
   printf ("Side = %5.2f Area = %5.2f\n", side, area);

   return 0;
}