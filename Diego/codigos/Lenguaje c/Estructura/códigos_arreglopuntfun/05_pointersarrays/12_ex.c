
// Pointers and Arrays 

#include <stdio.h>

int main(){

   int a[5], i;
   
   for(i = 0; i <= 4; i++){
      scanf("%d", &a[i]);
   }

   for(i = 0; i <= 4; i++){
      printf("a[%d] = %d\n",i,  a[i]);
   }
   
   return 0;
}