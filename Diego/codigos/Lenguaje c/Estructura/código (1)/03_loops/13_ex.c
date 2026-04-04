
// Loop

include <stdio.h>
 
int main(){

   // local variable definition
   int a = 0, b = 0; 

   // while loop execution
   printf("Output of while loop: \n");
   
   while(a < 5){
      a++;
      printf("a: %d\n", a);
   }

   printf("Output of do-while loop: \n");
   
   do{
      b++;
      printf("b: %d\n",b);
   } while(b < 5);

   return 0;
}