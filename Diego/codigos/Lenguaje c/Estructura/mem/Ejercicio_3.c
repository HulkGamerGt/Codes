#include <stdio.h>
#include <stdlib.h>

int main() {
    int filas, columnas, i, j;
    int **matriz;
    int sumaTotal = 0;

    printf("Ingrese el número de filas: ");
    scanf("%d", &filas);
    printf("Ingrese el número de columnas: ");
    scanf("%d", &columnas);

    matriz = (int **)malloc(filas * sizeof(int *));
    
    for (i = 0; i < filas; i++) {
        matriz[i] = (int *)malloc(columnas * sizeof(int));
    }

    printf("\n--- Ingreso de datos ---\n");
    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++) {
            printf("Matriz[%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    printf("\n--- Matriz Completa ---\n");
    for (i = 0; i < filas; i++) {
        int sumaFila = 0; 
        for (j = 0; j < columnas; j++) {
            printf("%d\t", matriz[i][j]);
            sumaFila += matriz[i][j];
            sumaTotal += matriz[i][j]; 
        }

        printf("| Suma fila: %d\n", sumaFila);
    }

    printf("\nSuma total de todos los elementos: %d\n", sumaTotal);

    for (i = 0; i < filas; i++) {
        free(matriz[i]);
    }

    free(matriz);
    return 0;
}