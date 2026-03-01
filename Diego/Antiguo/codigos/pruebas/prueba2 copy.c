
/*CLASES*/ 
#include <stdio.h>
#include <math.h>

int main() {
    int matriz[100000][100000];
    int num;
    int i, j;
    for (i = 0; i < 1000; i++) 
    {
        for (j = 0; j < 1000; j++) 
        {

          matriz[i][j] = rand() % 100; 
        }
    }// sumar las diagonales
    for (i = 0; i < 1000; i++) 
    {
        for (j = 0; j < 1000; j++) 
        {
            if (i == j) 
            {
                printf("%d ", matriz[i][j]);
            }
        }
        printf("\n");
    }




    /*printf("Diga un numero que se haya ingresado a la matriz: ");
    scanf("%d", &num);*/
    /*for (i = 0; i < 1000; i++) 
    {
        for (j = 0; j < 1000; j++) 
        {
            if (matriz[i][j] == num) 
            {
                printf("El numero %d se encuentra en la posicion [%d][%d]\n", num, i, j);
            }
        }
    }
    */
    return 0;
}