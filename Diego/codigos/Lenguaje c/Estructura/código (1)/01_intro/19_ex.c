
// Character inputs, using gets

#include <stdio.h>

int main(){

   char ch;
   
   printf("Enter a character: ");
   ch = getchar();
   
   puts("You entered: ");
   putchar(ch);
   
   printf("\nYou entered character: %c", ch);
   
   return 0;
}

