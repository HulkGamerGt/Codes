/*
 Diego solis R: 2025
 Fecha de inicio: 15/05/2025 08:12
 Fecha de termino: 15/05/2025 08:53
 Descripcion: Realice un algoritmo que pida numeros al usuario hasta que ingrese 10 positivos 
              y los muestre.
*/
#include <stdio.h>

int main(){
    int num=0, cont=0, sum=0;

    printf("Este codigo te dice cuales son los numeros positivos\n");

    while (cont < 10)
    {
        printf("Ingrese un numero positivo: ");
        scanf("%d", &num);
        if (num > 0)
        {
            printf("El numero %d es positivo\n", num);
            sum = sum + num;
            cont = cont + 1;
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
    printf("La suma de los numeros positivos es: %d\n", sum);
    printf("Se han ingresado 10 numeros positivos\n");

    return 0;
}
