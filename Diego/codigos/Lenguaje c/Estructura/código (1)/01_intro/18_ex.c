
// multiple character inputs

#include <stdio.h>

int main(){

   char ch1, ch2;
   
   printf("Enter two characters: ");
   scanf("%c %c", &ch1, &ch2);
   
   printf("You entered characters: %c and %c", ch1, ch2);
   
   return 0;
}