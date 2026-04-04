
// Arrays

#include <stdio.h>

int main(){
   int a[5] = {1,2, [4] = 4};
   int i;
   
   for(i = 0; i <= 4; i++){
      printf("a[%d]: %d\n", i, a[i]);
   }
   return 0;
}
