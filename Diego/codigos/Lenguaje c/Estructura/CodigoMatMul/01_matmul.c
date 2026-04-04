// librerias
#include <stdio.h>

// dimensiones
#define FILAS_A 2
#define COLS_A 3
#define FILAS_B 3
#define COLS_B 2

int main() {
    // matrices utilizadas
    int A[FILAS_A][COLS_A] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int B[FILAS_B][COLS_B] = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    // matriz resultante
    int C[FILAS_A][COLS_B] = {0};


    for (int i = 0; i < FILAS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            for (int k = 0; k < COLS_A; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("Matriz C:\n");
    for (int i = 0; i < FILAS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}