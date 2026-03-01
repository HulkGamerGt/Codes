#include <stdio.h>
//falta terminar
int sumar(int arreglo[], int tam)
{
    int suma = 0, i=0;
    for (i = 0; i < tam; i++)
    {
        suma = arreglo[i] + suma;
    }

    return suma;
}

int main (){


    int numeros[] = {1,2,7,5,9};
    int tam = sizeof(numeros) / sizeof(numeros[0]);

    int total = sumar(numeros , tam);
    printf("Suma total : %d", total);
    return 0;
}
