
// Decision making

#include <stdio.h>

int main() {
   int income = 5000;
   float tax;
   printf("Income: %d\n", income);

   if (income<10000){
      tax = (float)(income * 10 / 100);
      printf("tax: %f \n", tax);
   }
   else {
      tax= (float)(1000 + (income-10000) * 15 / 100);
      printf("tax: %f", tax);
   }
}

