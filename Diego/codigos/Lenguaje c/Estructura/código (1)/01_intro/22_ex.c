// String input 2

#include <stdio.h>
#include <stdlib.h>

int main(){

   char name[20];
   
   printf("Enter your name: ");
   fgets(name, sizeof(name), stdin);
   
   printf("You entered the name: %s", name);
   
   return 0;
}