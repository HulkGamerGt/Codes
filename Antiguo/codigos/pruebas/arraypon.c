#include <stdio.h>

int main (){

    int arraybidi[3][4]; 
    int i = 0;
    int j = 0;

    printf("ingrese valores para el arreglo 3 x 4\n");

    for( i = 0; i < 3; i++)
    {
        for(j = 0; j < 4 ; j++)
        {
            printf("Arreglo [%d][%d] : ", i , j);
            scanf("%d",&arraybidi[i][j]);
        }
    }

    for ( i = 0; i < 3; i++)
    {
        for(j = 0; j < 4 ; j++)
        {
            printf("El arreglo[%d][%d] es: %d \n",i,j,arraybidi[i][j]);
        }
    }
    return 0;
}