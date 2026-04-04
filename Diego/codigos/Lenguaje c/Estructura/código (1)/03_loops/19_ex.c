
// Break statement loop

#include <stdio.h>
#include <string.h>

int main () {

   char string[] = "Rhythmic";
   int len = strlen(string);
   int i;

   for (i = 0; i < len; i++){
      if (string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u')
         break;
      printf("%c\n", string[i]);
   }

   return 0;
}