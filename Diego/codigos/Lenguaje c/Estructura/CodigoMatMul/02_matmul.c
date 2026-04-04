
#include <stdio.h>

#define FILAS_A 2
#define COLS_A 3
#define FILAS_B 3
#define COLS_B 2

int main() {
    // matrices a usar
    int A[FILAS_A * COLS_A] = {
        1, 2, 3,
        4, 5, 6
    };

    int B[FILAS_B * COLS_B] = {
        7, 8,
        9, 10,
        11, 12
    };

    int C[FILAS_A * COLS_B] = {0};

    int total = FILAS_A * COLS_B * COLS_A;

    for (int t = 0; t < total; t++) {

        int i = t / (COLS_B * COLS_A);
        int j = (t / COLS_A) % COLS_B;
        int k = t % COLS_A;

        C[i * COLS_B + j] += 
            A[i * COLS_A + k] * 
            B[k * COLS_B + j];
    }

    printf("Matriz C:\n");
    for (int i = 0; i < FILAS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            printf("%d ", C[i * COLS_B + j]);
        }
        printf("\n");
    }

    return 0;
}