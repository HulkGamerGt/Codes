
// Functions for inputs

#include <stdio.h>

int main(){

   int price, qty, ttl;

   printf("Enter price and quantity: ");
   scanf("%d %d", &price, &qty);

   ttl = price * qty;

   printf("Total : %d", ttl);
   
   return 0;
}