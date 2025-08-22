#include <stdio.h>
/*CLASES*/

int main() {
    int matriz[3][3];
    int matriz2[3][3];
    int matriz3[3][3];
    int i, j;
    for (i = 0; i < 3; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            printf("Ingrese el elemento [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    printf("Ingrese los elementos de la segunda matriz:\n");
    for (i = 0; i < 3; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            printf("Ingrese el elemento [%d][%d]: ", i, j);
            scanf("%d", &matriz2[i][j]);
        }
    }
    for (i = 0; i < 3; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            matriz3[i][j] = matriz[i][j] + matriz2[i][j];
        }
    }
    printf("Matriz resultante:\n");
    for (i = 0; i < 3; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            printf("%d    ", matriz3[i][j]);
        }
        printf("\n");
    }


   return 0;
}
