
// Return pointer from function

#include <stdio.h>
#include <string.h>

struct rectangle{
   float len, brd;
   double area;
};

struct rectangle * area(float x, float y);

int main(){

   struct rectangle *r;
   float x, y;
   x = 10.5, y = 20.5;
   r = area(x, y);

   printf("Length: %f \nBreadth: %f \nArea: %lf\n", r->len, r->brd, r->area);

   return 0;
}

struct rectangle * area(float x, float y){
   double area = (double)(x*y);
   static struct rectangle r;
   r.len = x; r.brd = y; r.area = area;
   
   return &r;
}