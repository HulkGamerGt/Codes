
// pointer Arithmetic

#include <stdio.h>

int main(){

   int x = 10;
   int *y = &x;

   printf("Value of y before increment: %d\n", y);

   y++;

   printf("Value of y after increment: %d", y);
}