
// Continue statement in loop

#include <stdio.h>
#include <string.h>

int main () {

   char string[] = "Welcome to TutorialsPoint C Tutorial";
   int len = strlen(string);
   int i;

   printf("Given string: %s\n", string);
   printf("after removing the vowels\n");

   for (i=0; i<len; i++){
      if (string[i]=='a' || string[i]=='e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u')
         continue;
      printf("%c", string[i]);
   }

   return 0;
}