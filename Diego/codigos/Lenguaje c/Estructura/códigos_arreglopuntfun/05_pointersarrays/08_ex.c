
#include <stdio.h>

int main(){

   float var1 = 10.55;
   float *floatptr = &var1;
   
   printf("var1: %f \nAddress of var1: %p \n\n",var1, &var1);
   printf("floatptr: %p \nAddress of floatptr: %p \n\n", floatptr, &floatptr);
   printf("var1: %f \nValue at floatptr: %f", var1, *floatptr);
   
   return 0;
}