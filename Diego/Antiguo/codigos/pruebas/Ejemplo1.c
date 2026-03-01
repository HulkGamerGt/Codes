#include <stdio.h>
//  Diego Solis R: 2025
int main() {
    int num = 0;
    int i = 0;
    

    while (i < 10)
    {
        printf("Ingresar un numero positivo \n"); 
        scanf("%d", &num);
        if (num > 0)
        {
            printf("El numero %d es positivo \n", num);
            i = i + 1;
        }
        else if (num < 0)  
        {
          printf("Es un numero negativo \n");
        }
    }
    printf("Se han ingresado 10 numeros positivos \n");
}
