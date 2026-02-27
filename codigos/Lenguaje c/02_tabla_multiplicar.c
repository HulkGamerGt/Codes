#include <stdio.h>

int main () {
 
    int num = 0, i = 1;
  // Este codigo hace una tabla de multiplicar
    printf("Este codigo hace una tabla de multiplicar\n");
    printf("Introduce un numero: ");
    scanf("%d", &num);

    while (i <= 10){
  
     if (num > 0) 
        {
          printf("%d x %d = %d\n", num, i, num * i);
        }
        i++;    
        
      }

    return 0;
}