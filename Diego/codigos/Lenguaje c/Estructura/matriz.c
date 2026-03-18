#include <stdio.h>

int main() {
    int Q, W, E, R;

    printf("Filas matriz 1: "); scanf("%d", &Q);
    printf("Columnas matriz 1: "); scanf("%d", &W);
    printf("Filas matriz 2: "); scanf("%d", &E);
    printf("Columnas matriz 2: "); scanf("%d", &R);

    if (W != E) {
        printf("Error: Las columnas de A deben coincidir con las filas de B.\n");
        return 1;
    }

    int A[Q][W], B[E][R], C[Q][R];

    // Inicializar C en 0
    for(int i=0; i<Q; i++)
        for(int j=0; j<R; j++) C[i][j] = 0;

    // Leer Matriz A
    for(int n=0; n<Q; n++) {
        for(int l=0; l<W; l++) {
            printf("A[%d][%d]: ", n, l);
            scanf("%d", &A[n][l]); // Se agregó el &
        }
    }

    // Leer Matriz B
    for(int n=0; n<E; n++) {
        for(int l=0; l<R; l++) { // Se corrigió el límite a R
            printf("B[%d][%d]: ", n, l);
            scanf("%d", &B[n][l]); // Se agregó el &
        }
    }

    // Multiplicación Lógica Correcta
    for(int i=0; i<Q; i++) {       // Filas de A
        for(int j=0; j<R; j++) {   // Columnas de B
            for(int k=0; k<W; k++) { // Factor común
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Imprimir Resultado
    printf("\nResultado Matriz C:\n");
    for(int i=0; i<Q; i++) {
        for(int j=0; j<R; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}