
// Pointer to structures

#include <stdio.h>
#include <string.h>

struct person{
   char *name;
   int age;
   float weight;
};

int main(){

   struct person *personPtr, person1;

   strcpy(person1.name, "Meena");
   person1.age = 40;
   person1.weight = 60;

   personPtr = &person1;

   printf("Displaying the Data: \n");
   printf("Name: %s\n", personPtr -> name);
   printf("Age: %d\n", personPtr -> age);
   printf("Weight: %f", personPtr -> weight);
   
   return 0;
}