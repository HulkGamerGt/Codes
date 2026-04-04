
// NULL pointer

#include <stdio.h>
#include <string.h>

int main(){

   FILE *fp;
   char *s;
   int i, a;  
   float p;

   fp = fopen ("file3.txt", "r");

   if (fp == NULL){
      puts ("Cannot open file"); return 0;
   }

   while (fscanf(fp, "%d %f %s", &a, &p, s) != EOF)
      printf ("Name: %s Age: %d Percent: %f\n", s, a, p);

   fclose(fp);
   
   return 0;
}