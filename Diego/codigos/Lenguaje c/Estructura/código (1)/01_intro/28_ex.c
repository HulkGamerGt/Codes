
// Constant using define

#include <stdio.h>
#define LENGTH 10   
#define WIDTH  5
#define NEWLINE '\n'

int main() {
   int area;  
   area = LENGTH * WIDTH;
   printf("length: %d width: %d", LENGTH, WIDTH);
   printf("%c", NEWLINE);
   printf("value of area : %d", area);
   return 0;
}