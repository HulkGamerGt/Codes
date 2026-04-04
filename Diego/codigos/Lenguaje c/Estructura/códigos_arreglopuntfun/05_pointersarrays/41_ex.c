
// Return pointer from function

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *hellomsg(char *);

int main(){

   char *name = "TutorialsPoint";
   char *arr = hellomsg(name);
   printf("%s\n", arr);
   
   return 0;
}

char *hellomsg(char *x){
   char *arr = (char *)malloc(50*sizeof(char));
   strcpy(arr, "Hello ");
   strcat(arr, x);
   
   return arr;
}