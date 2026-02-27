// Descripcion: Este programa solicita al usuario ingresar 8 números y determina si cada uno es par o impar.
#include <stdio.h>
int main(void)
{
    int num = 0, i = 0, par = 0, impar = 0;
    int numeros[8];

    for (i=0; i < 8; i++)
    {
        printf("Ingrese el numero %d: ", i+1);
        scanf("%d", &num);
        numeros[i] = num;
    }
    for (i=0 ; i < 8; i++)
    {
        if(numeros[i] % 2 == 0)
        {
            printf("El numero %d es par\n", numeros[i]);
            par++;
        }
        else
        {
            printf("El numero %d es impar\n", numeros[i]);
            impar++;
        }
    }
    printf("Total de numeros pares: %d\n", par);
    printf("Total de numeros impares: %d\n", impar);
}