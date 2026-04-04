
// Pointer to function

#include <stdio.h>

int compare(char *, char *);

int main(){

   char str1[] = "BAT";
   char str2[] = "BALL";
   int ret = compare(str1, str2);
   
   return 0;
}

int compare (char *x, char *y){

   int val;

   if (strlen(x) > strlen(y)){
      printf("Length of Str1 is greater than or equal to the length of Str2");
   }
   else{
      printf("Length of Str1 is less than the length of Str2");
   }
}