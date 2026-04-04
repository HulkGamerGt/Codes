
// Program structure

/*Headers*/
#include <stdio.h>
#include <math.h>

/*forward declaration*/
float area_of_square(float);

/*main function*/
int main() {
   /* my first program in C */
   float side = 5.50;
   float area = area_of_square(side);
   printf ("Side=%5.2f Area=%5.2f\n", side, area);
   return 0;
}

/*subroutine*/
float area_of_square(float side){
   float area = pow(side,2);
   return area;
}