#include <stdio.h>
/*CLASES*/

void escanea(int matriz[3][3]);
void muetranormal(int matriz[3][3]);
void muestrabienmatriz(int matriz[3][3]);

int main() {
    int matriz[3][3];

    escanea(matriz);
    muetranormal(matriz);
    muestrabienmatriz(matriz);
    return 0;
}
void escanea(int matriz[3][3]){
    int i, j;
    for (i = 0; i < 3; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            printf("Ingrese el elemento [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
}
void muetranormal(int matriz[3][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("Elemento [%d][%d]: %d \n", i, j, matriz[i][j]);
        }
    }
}
void muestrabienmatriz(int matriz[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++) 
      {
        for (j = 0; j < 3; j++) 
        {
            printf("%d    ", matriz[i][j]);
        }
        printf("\n");
    }
}