
/*CLASES*/
#include <stdio.h>

int main() {
    int matriz[10][10];
    int num;0
    int i=0,j
    for (i = 0; i < 10; i++) 
    {
        for (j = 0; j < 10; j++) 
        {
            printf("Ingrese el elemento [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    printf("Diga un numero que se haya ingresado a la matriz: ");
    scanf("%d", &num);
    for (i = 0; i < 10; i++) 
    {
        for (j = 0; j < 10; j++) 
        {
            if (matriz[i][j] == num) 
            {
                printf("El numero %d se encuentra en la posicion [%d][%d]\n", num, i, j);
            }
        }
    }
    return 0;
}