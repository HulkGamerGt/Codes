
// Pointer to function

#include <stdio.h>
#include <string.h>

struct rectangle{
   float len, brd;
   double area;
};

int area(struct rectangle *);

int main(){

   struct rectangle s;
   printf("Input length and breadth of a rectangle");
   scanf("%f %f", &s.len, &s.brd);
   area(&s);

   return 0;

}

int area(struct rectangle *r){

   r->area = (double)(r->len*r->brd);
   printf("Length: %f \n Breadth: %f \n Area: %lf\n", r->len, r->brd, r->area);
   
   return 0;
}