// Descripcion: Este programa solicita al usuario ingresar 8 números y determina si cada uno es par o impar.
#include <stdio.h>
int main(void)
{
    int num = 0, i = 0,h = 0;
    int numeros[5];

    //for (i = 0; i < 5; i++)
    //{
   //     printf("Ingrese el numero %d: ", i+1);
   //     scanf("%d", &num);
   //     numeros[i] = num;
    //}
    //for (i = 4; i >= 0; i--)
   // printf("numero %d es %d\n", i+1, numeros[i]);

   for (i = 4; i >= 0; i--)
    {   
        printf("Ingrese el numero %d: ", h+1);
        scanf("%d", &num);
        numeros[i] = num;
        h++;
    }
    for (i = 0; i < 5; i++)
    printf("numero %d es %d\n", i+1, numeros[i]);

}