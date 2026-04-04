
// Multi-line comments

/* program to calculate area of square */

/* headers */
#include <stdio.h>
#include <math.h>

/* forward declaration of function */
float area_of_square(float);


/* main function */
int main(){

   /* variable declaration */
   float side = 5.50;
   
   /* calling function */
   float area = area_of_square(side);
   printf("Side = %5.2f Area = %5.2f", side, area);

   return 0;
}

/* User-defined function to calculate
the area of square. It takes side as the argument 
and returns the area */

float area_of_square(float side){
   float area = pow(side, 2);
   return area;
}