
// Reading a character sequence

#include <stdio.h>

int main(){

   char ch;
   char word[10];

   int i = 0;
   printf("Enter characters. End by pressing the Enter key: ");
   
   while(1){
      ch = getchar();
      word[i] = ch;
      if (ch == '\n')
         break;
      i++;
   }
   printf("\nYou entered the word: %s", word);
   
   return 0;
}