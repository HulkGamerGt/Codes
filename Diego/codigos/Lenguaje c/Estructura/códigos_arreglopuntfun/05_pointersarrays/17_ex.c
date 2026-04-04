
// Applications of pointer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

   char *name;
   name = (char *) malloc(strlen("TutorialsPoint"));

   strcpy(name, "TutorialsPoint");
   
   if(name == NULL) {
      fprintf(stderr, "Error - unable to allocate required memory\n");
   } else {
      printf("Name = %s\n", name );
   }
}