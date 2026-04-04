
// void pointer

#include <stdio.h>

int main(){

   int a = 10;
   char b = 'x';

   // void pointer holds address of int a
   void *ptr = &a;
   printf("Address of 'a': %d", &a);
   printf("\nVoid pointer points to: %d", ptr);

   // it now points to char b
   ptr = &b;
   printf("\nAddress of 'b': %d", &b);
   printf("\nVoid pointer points to: %d", ptr);
}

