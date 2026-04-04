// pointer vs array

##include <stdio.h>

int main (){

   /* an array with 5 elements */
   int arr[5] = {10, 20, 30, 40, 50};

   int i;

   /* output each array element's value */
   printf("Array values with subscripts: \n");

   for(i = 0; i < 5; i++){
      printf("arr[%d]: %d\n", i, arr[i]);
   }
   
   return 0;
}