
// Function pointer 

#include <stdio.h>

int addition (int a, int b){
   return a + b;
}

int main(){

   int (*ptr)(int, int) = addition;
   int x = 10, y = 20;
   int z = (*ptr)(x, y);

   printf("Addition of x: %d and y: %d = %d", x, y, z);
   
   return 0;
}
