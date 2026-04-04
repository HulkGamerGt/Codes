
// pointer to structures

#include <stdio.h>
#include <string.h>

struct book{
   char title[10];
   double price;
   int pages;
};

int main(){
   
   struct book b1 = {"Learn C", 675.50, 325};
   struct book *strptr;
   strptr = &b1;
   
   printf("Title: %s\n", strptr -> title);
   printf("Price: %lf\n", strptr -> price);
   printf("No of Pages: %d\n", strptr -> pages);

   return 0;
}

