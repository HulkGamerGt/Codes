/*
 Diego solis R: 2025
 Fecha de inicio: 15/05/2025 08:12
 Fecha de termino: 15/05/2025 08:53
 Descripcion: este codigo te dice si un numero es primo o no.
*/
#include <stdio.h>

int main(){
    int num=0, cont=0, esPrimo=0;

    printf("Este codigo te dice si un numero es primo o no\n");

    while (cont < 10)
    {
        printf("Ingrese un numero positivo: ");
        scanf("%d", &num);
        if (num > 1)
        {
            printf("El numero %d es positivo\n", num);
            cont = cont + 1;
            int esPrimo = 1; // Suponemos que el número es primo
            for (int i = 2; i <= num / 2; i++)
            {
                if (num % i == 0)
                {
                    esPrimo = 0; // No es primo
                    break;
                }
            }
            if (esPrimo)
            {
                printf("El numero %d es primo\n", num);
            }
            else
            {
                printf("El numero %d no es primo\n", num);
            }
        }
        if (num < 0)
        {
         printf("El numero no es positivo, debe ingresar otro numero\n");
        }
        if (num == 0)
        {
         printf("El numero 0 es neutro, ingresa uno solo positivo\n");
        }
    }
    printf("Se han ingresado 10 numeros primos\n");

    return 0;
}