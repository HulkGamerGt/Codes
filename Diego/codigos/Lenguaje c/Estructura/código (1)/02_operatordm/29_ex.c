
// Decision making

#include <stdio.h>
 
int main () {

   // local variable declaration
   int amount;
   float discount, net;
   
   /*Run the program for different values 
   of amount – 500, 2250 and 5200. Blocks in 
   respective conditions will be executed*/
   
   // change to 2250 and 5200 and run again
   amount = 500;  
   
   if (amount < 1000){
      discount=0;
   }
   if (amount >= 1000 && amount<5000){
      discount=5;
   }
   if (amount >= 5000){
      discount=10;
   }
   net = amount - amount*discount/100;
   printf("Amount: %d Discount: %f Net payable: %f", amount, discount, net);
   
   return 0;
}