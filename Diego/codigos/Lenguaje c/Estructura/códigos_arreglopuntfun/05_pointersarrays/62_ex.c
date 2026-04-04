
// void pointer

#include <stdio.h>

int main(){

   void *arr[3];

   int a = 100;
   float b = 20.5;
   char *c = "Hello";

   arr[0] = &a;
   arr[1] = &b;
   arr[2] = &c;

   printf("Integer: %d\n", *((int *)arr[0]));
   printf("Float: %f\n", *((float *)arr[1]));
   printf("String: %s\n", *((char **)arr[2]));

   return 0;
}