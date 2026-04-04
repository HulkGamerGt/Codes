
// Nested loop with break statement 

#include <stdio.h>

int main(){
   int i, num, n, flag;
   printf("The prime numbers in between the range 1 to 30:\n");
   
   for(num = 2; num <= 30; num++){
      flag = 0;
      for(i = 2; i <= num/2; i++){
         if(num % i == 0){
            flag++;
            break;
         }
      }
      if(flag == 0)
         printf("%d is prime\n",num);
   }
   return 0;
}