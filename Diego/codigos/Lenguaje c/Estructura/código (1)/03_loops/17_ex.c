
// Nested loop

#include <stdio.h>
#include <string.h>

int main(){

   int i, j, l;
   char x[] = "TutorialsPoint";
   l = strlen(x);

   // outer loop
   for(i = 0; i < l; i++){
   
      // inner loop
      for(j = 0; j <= i; j++){
         printf("%c", x[j]);
      }
      printf("\n");
   }
   return 0;
}