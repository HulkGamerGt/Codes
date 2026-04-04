
// sizeof with struct data

#include <stdio.h>

struct employee {
   char name[10];
   int age;
   double percent;
};

int main(){
   struct employee e1 = {"Raghav", 25, 78.90};
   printf("Size of employee variable: %d\n",sizeof(e1));   
   return 0;
}